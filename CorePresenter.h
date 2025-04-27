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
    Q_PROPERTY(quint64 progress READ progress NOTIFY progressChanged)
    Q_PROPERTY(quint64 wordCount READ wordCount NOTIFY wordCountChanged)
public:
    CorePresenter();
    CorePresenter(const CorePresenter& _other) = delete;
    CorePresenter(CorePresenter&& _other) = delete;

    CorePresenter& operator=(const CorePresenter& _other) = delete;
    CorePresenter& operator=(CorePresenter&& _other) = delete;

    ~CorePresenter();



    Q_INVOKABLE void readFile(const QString& _path);
    Q_INVOKABLE void resumeProcessing();
    Q_INVOKABLE void pauseProcessing();
    Q_INVOKABLE void resetProcessing();

//property related methods
    MyMapModel* mapModel() { return &m_MapModel; }

    quint64 progress() const { return m_Progress; }
    void setProgress(quint64 newValue) {
        if (m_Progress != newValue) {
            m_Progress = newValue;
            emit progressChanged();
        }
    }
    void updateProgress(quint64 newVal) {
        setProgress(m_Progress + newVal);
    }

    quint64 wordCount() const { return m_WordCount; }
    void setWordCount(quint64 newValue) {
        if (m_WordCount != newValue) {
            m_WordCount = newValue;
            emit wordCountChanged();
        }
    }
signals:
    void request_readFile(QString _path);
//property related signals
    void progressChanged();
    void wordCountChanged();
private slots:
    void on_response_readFile(Core::ErrorCodes _code);
    void on_wordFound_from_Core(QString _word) {
        m_PendingWords.push(_word);
    }
    void on_fileInfo_from_Core(uint64_t _wordCount);
    void on_processTimer_timeout();

private:
    void initSignalSlotMechanism();

    QThread coreThread;

    MyMapModel m_MapModel;

    std::unique_ptr<Core, CoreDeleter> m_CorePtr;

    std::queue<QString> m_PendingWords;

    bool m_IsJobPending = false;
    bool m_IsPaused = false;
    bool m_IsJobDone = false;

    QTimer m_ProcessTimer;

    //properties
    quint64 m_Progress  = 0;
    quint64 m_WordCount = 0;
};

#endif // COREPRESENTER_H
