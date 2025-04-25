#ifndef COREPRESENTER_H
#define COREPRESENTER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "Core.h"
#include "MyMapModel.h"
#include <QTimer>
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

        emit request_readFile(_path);
    }
signals:
    void request_readFile(QString _path);
private slots:
    void on_response_readFile(Core::ErrorCodes _code) {
        qWarning() << "response received!" << static_cast<int>(_code);
    }
    void on_wordFound_from_Core(QString _word) {
        qWarning() << "Word found from core: " << _word;
        m_MapModel.insert(_word);
    }

    void on_fileInfo_from_Core(uint64_t _wordCount) {
        qWarning() << "WordCount found from core: " << _wordCount;
    }
private:
    void initSignalSlotMechanism() {
        QObject::connect(this, &CorePresenter::request_readFile, m_CorePtr.get(), &Core::on_request_readFile);
        QObject::connect(m_CorePtr.get(), &Core::respone_readFile, this, &CorePresenter::on_response_readFile);
        QObject::connect(m_CorePtr.get(), &Core::wordFound, this, &CorePresenter::on_wordFound_from_Core);
        QObject::connect(m_CorePtr.get(), &Core::fileInfo, this, &CorePresenter::on_fileInfo_from_Core);
    }

    QThread coreThread;

    MyMapModel m_MapModel;

    std::unique_ptr<Core, CoreDeleter> m_CorePtr;

};

#endif // COREPRESENTER_H
