#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>
#include <Windows.h>
#include <commdlg.h>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QLoggingCategory>
#include "WindowsHelper.h"
#include "CorePresenter.h"
void registerQmlTypes() {
    qmlRegisterSingletonType<WindowsHelper>("com.twogis.test", 1, 0, "WindowsHelper",
    [](QQmlEngine *engine, QJSEngine *) -> QObject* {
        Q_UNUSED(engine)
        return new WindowsHelper();
    });
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
