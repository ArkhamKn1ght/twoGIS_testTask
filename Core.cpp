#include "Core.h"


Core::ErrorCodes Core::readFile(const QString &_path) {
    QFile file(_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file!";
        return ErrorCodes::FAILED_TO_OPEN_FILE;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(' ');

        for (const QString& word : words)
            if(word.size() > 0) emit wordFound(word);
    }

    file.close();
    return ErrorCodes::OK;
}
