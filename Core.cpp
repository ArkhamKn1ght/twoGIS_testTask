#include "Core.h"

Core::ErrorCodes Core::processFile(const QString &_path) {
    QFile file(_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return ErrorCodes::FAILED_TO_OPEN_FILE;
    }

    {
        QTextStream in(&file);
        uint64_t wordCount = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(' ', Qt::SkipEmptyParts);
            wordCount += words.size();
        }
        emit fileInfo(wordCount);
        file.reset();
    }

    {

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList words = line.split(' ', Qt::SkipEmptyParts);

            for (const QString& word : words)
                emit wordFound(word);

        }
    }

    file.close();
    return ErrorCodes::OK;
}
