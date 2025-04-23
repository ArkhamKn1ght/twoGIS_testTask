#ifndef COREPRESENTER_H
#define COREPRESENTER_H

#include <QObject>
#include <QDebug>
#include "Core.h"
#include <QThread>
class CorePresenter : public QObject
{
    Q_OBJECT
public:
    CorePresenter() {
        qWarning() << "CorePresenter constructed";
        ptr = std::unique_ptr<Core, CoreDeleter>(new Core());
        ptr->moveToThread(&coreThread);
        coreThread.start();
    }
private:
    struct CoreDeleter {
        void operator()(Core* p) const {
            qWarning() << "Functor deleter" << p;
            p->deleteLater();
        }
    };

    std::unique_ptr<Core, CoreDeleter> ptr;
    QThread coreThread;
};

#endif // COREPRESENTER_H
