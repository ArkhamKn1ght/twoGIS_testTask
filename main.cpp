#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>
#include <Windows.h>
#include <commdlg.h>
#include <QString>
#include <QDebug>
#include <QApplication>
#include "WindowsHelper.h"
#include "CorePresenter.h"
void registerQmlTypes() {
    //qmlRegisterType<MyMapModel>("com.twogis.test", 1, 0, "MyMapModel");
    qmlRegisterSingletonType<WindowsHelper>("com.twogis.test", 1, 0, "WindowsHelper",
    [](QQmlEngine *engine, QJSEngine *) -> QObject* {
        Q_UNUSED(engine)
        return new WindowsHelper();
    });
}

int readFile(const QString& _path) {
    QFile file(_path); // Replace with your file path
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file!";
        return -1;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList words = line.split(' ');
        for (const QString& word : words) {
            if(word.size() == 0) continue;
            qDebug() << "Word:" << word.trimmed();
        }
    }

    file.close();
    return 0;
}

int main(int argc, char *argv[])
{

    registerQmlTypes();
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    CorePresenter corePresenter;
    engine.rootContext()->setContextProperty("corePresenter", &corePresenter);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("twoGIS_testTask", "Main");

    return app.exec();
}
