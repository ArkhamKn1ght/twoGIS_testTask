#include "CorePresenter.h"

CorePresenter::CorePresenter() {
    m_CorePtr = std::unique_ptr<Core, CoreDeleter>(new Core());
    m_CorePtr->moveToThread(&coreThread);

    initSignalSlotMechanism();
    coreThread.start();
}

CorePresenter::~CorePresenter() {
    if(coreThread.isRunning()) {
        coreThread.quit();
        coreThread.wait();
    }
}
