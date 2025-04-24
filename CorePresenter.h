#ifndef COREPRESENTER_H
#define COREPRESENTER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "Core.h"
#include "MyMapModel.h"
#include <QTimer>
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
    CorePresenter() {
        m_CorePtr = std::unique_ptr<Core, CoreDeleter>(new Core());
        m_CorePtr->moveToThread(&coreThread);
        coreThread.start();
        m_MapModel.insert("aboba", 5);
        m_MapModel.insert("aboba1", 6);
        m_MapModel.insert("aboba2", 7);
        QTimer::singleShot(3000, [&]() {
            m_MapModel.insert("ABOBA4", 10);
        });
    }
    ~CorePresenter() {
        if(coreThread.isRunning()) {
            coreThread.quit();
            coreThread.wait();
        }
    }

    MyMapModel* mapModel() { return &m_MapModel; }

signals:
    void nameChanged();

private:
    MyMapModel m_MapModel;
    std::unique_ptr<Core, CoreDeleter> m_CorePtr;
    QThread coreThread;
};

#endif // COREPRESENTER_H
