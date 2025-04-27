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

void CorePresenter::readFile(const QString &_path) {
    if(m_IsJobPending) {
        resumeProcessing();
    } else if( !m_IsJobDone ) {
        m_IsJobPending = true;
        m_ProcessTimer.start(100);
        emit request_readFile(_path);
    }
}

void CorePresenter::resumeProcessing() {
    if (!m_IsPaused || m_IsJobDone) return;

    m_ProcessTimer.start(100);
    m_IsPaused = false;
}

void CorePresenter::pauseProcessing() {
    qWarning() << m_IsPaused << m_IsJobDone;
    if (m_IsPaused || m_IsJobDone) return;

    m_ProcessTimer.stop();
    m_IsPaused = true;
}

void CorePresenter::resetProcessing() {
    std::queue<QString> empty;
    std::swap(m_PendingWords, empty);

    m_MapModel.clear();

    m_IsJobPending = false;
    m_IsPaused = false;
    m_IsJobDone = false;

    m_ProcessTimer.stop();

    m_Progress = 0;
}

void CorePresenter::on_response_readFile(Core::ErrorCodes _code) {
}

void CorePresenter::on_fileInfo_from_Core(uint64_t _wordCount) {
    setWordCount(_wordCount);
}

void CorePresenter::on_processTimer_timeout() {
    if( !m_IsJobPending || m_IsPaused ) return;

    static constexpr int processingStep = 1000;
    int counter = processingStep;
    while(m_PendingWords.size() && counter) {
        m_MapModel.insertNoUpdate(m_PendingWords.front());
        m_PendingWords.pop();
        --counter;
    }

    updateProgress(processingStep - counter);

    m_MapModel.forceUpdate();
    if(m_PendingWords.size() == 0) {
        m_ProcessTimer.stop();
        m_IsJobPending = false;
        m_IsJobDone = true;
    }
}

void CorePresenter::initSignalSlotMechanism() {
    QObject::connect(this, &CorePresenter::request_readFile, m_CorePtr.get(), &Core::on_request_readFile);
    QObject::connect(m_CorePtr.get(), &Core::respone_readFile, this, &CorePresenter::on_response_readFile);
    QObject::connect(m_CorePtr.get(), &Core::wordFound, this, &CorePresenter::on_wordFound_from_Core);
    QObject::connect(m_CorePtr.get(), &Core::fileInfo, this, &CorePresenter::on_fileInfo_from_Core);

    QObject::connect(&m_ProcessTimer, &QTimer::timeout, this, &CorePresenter::on_processTimer_timeout);
}
