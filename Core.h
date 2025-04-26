#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QDebug>
#include <QFile>
class Core : public QObject
{
    Q_OBJECT
public:
    enum class ErrorCodes {
        OK = 0,
        FAILED_TO_OPEN_FILE
    };

public:
    Core() {}
    ~Core() {}
signals:
    void wordFound(QString _words);
    void fileInfo(uint64_t _wordCount);
    void respone_readFile(ErrorCodes _code);

public slots:
    void on_request_readFile(QString _path) {
        emit respone_readFile( processFile(_path) );
    }
private:
    ErrorCodes processFile(const QString& _path);
};

#endif // CORE_H
