#ifndef COREPRESENTER_H
#define COREPRESENTER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "Core.h"
#include "MyMapModel.h"
#include <QTimer>
#include <queue>
//implement some queue or list that holds  up to 15 iterators to items in map
//in descending(or ascending) order

class CorePresenter : public QObject
{
private:

    struct CoreDeleter {
        void operator()(Core* p) const {
            p->deleteLater();
        }
    };

    Q_OBJECT
    Q_PROPERTY(MyMapModel* mapModel READ mapModel CONSTANT)
public:
    CorePresenter();
    ~CorePresenter();

    MyMapModel* mapModel() { return &m_MapModel; }

    Q_INVOKABLE void readFile(const QString& _path) {
        if(!m_IsJobPending) {
            m_IsJobPending = true;
            m_ProcessTimer.start(100);
            emit request_readFile(_path);
        }
    }

    Q_INVOKABLE void resumeProcessing() {
        qWarning() << "resuming 1";
        if (!m_IsPaused) return;
        qWarning() << "resuming 2";
        m_ProcessTimer.start(100);
        m_IsPaused = false;
    }

    Q_INVOKABLE void pauseProcessing() {
        qWarning() << "pausing 1";
        if (m_IsPaused) return;
        qWarning() << "pausing 2";
        m_ProcessTimer.stop();
        m_IsPaused = true;
    }

signals:
    void request_readFile(QString _path);
private slots:
    void on_response_readFile(Core::ErrorCodes _code) {
        qWarning() << "response received!" << static_cast<int>(_code);
    }
    void on_wordFound_from_Core(QString _word) {
        m_PendingWords.push(_word);


    }

    void on_fileInfo_from_Core(uint64_t _wordCount);

    void on_processTimer_timeout();




private:
    void initSignalSlotMechanism() {
        QObject::connect(this, &CorePresenter::request_readFile, m_CorePtr.get(), &Core::on_request_readFile);
        QObject::connect(m_CorePtr.get(), &Core::respone_readFile, this, &CorePresenter::on_response_readFile);
        QObject::connect(m_CorePtr.get(), &Core::wordFound, this, &CorePresenter::on_wordFound_from_Core);
        QObject::connect(m_CorePtr.get(), &Core::fileInfo, this, &CorePresenter::on_fileInfo_from_Core);

        QObject::connect(&m_ProcessTimer, &QTimer::timeout, this, &CorePresenter::on_processTimer_timeout);
    }

    QThread coreThread;

    MyMapModel m_MapModel;

    std::unique_ptr<Core, CoreDeleter> m_CorePtr;

    std::queue<QString> m_PendingWords;
    bool m_IsJobPending = false;
    bool m_IsPaused = false;
    QTimer m_ProcessTimer;
};

#endif // COREPRESENTER_H
