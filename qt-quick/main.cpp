#include "surface.h"
#include "mainwindow.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<MainWindow>("com.ics.demo", 1, 0, "MainWindow");
//    qmlRegisterUncreatableType<MainWindow::Sh>("com.ics.demo", 1, 0, "Sh", "Shading enum. It cannot be instantiated.");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
