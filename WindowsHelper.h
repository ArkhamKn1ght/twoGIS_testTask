#ifndef WINDOWSHELPER_H
#define WINDOWSHELPER_H

#include <QObject>
#include <QFileDialog>
class WindowsHelper : public QObject
{
    Q_OBJECT
public:
    explicit WindowsHelper(QObject *parent = nullptr) : QObject(parent) {}

    static Q_INVOKABLE QString openFileDialog() {
        QString file = QFileDialog::getOpenFileName(nullptr, "Select a file", "", "All Files (*.*)");
        return file;
    }
};

#endif // WINDOWSHELPER_H
