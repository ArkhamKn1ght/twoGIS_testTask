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

void CorePresenter::on_fileInfo_from_Core(uint64_t _wordCount) {

}

void CorePresenter::on_processTimer_timeout() {
    if( !m_IsJobPending || m_IsPaused ) return;

    int counter = 1000;
    while(m_PendingWords.size() && counter) {
        m_MapModel.insertNoUpdate(m_PendingWords.front());
        m_PendingWords.pop();
        --counter;
    }
    m_MapModel.forceUpdate();
    if(m_PendingWords.size() == 0) {
        m_ProcessTimer.stop();
        m_IsJobPending = false;
    }
    qWarning() << "job done, " << m_PendingWords.size() << "words left to go";
}
