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
    Core() {}
    ~Core() {}
signals:
    void wordFound(QString _word);

    void respone_readFile(ErrorCodes _code);
public slots:
    void on_request_readFile(QString _path) {
        emit respone_readFile( readFile(_path) );
    }
private:
    ErrorCodes readFile(const QString& _path);
};

#endif // CORE_H
