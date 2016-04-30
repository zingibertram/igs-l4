#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setStyle(QStyleFactory::create("Fusion"));
//    QPalette p = a.palette();
//    p.setColor(QPalette::Window, QColor(53, 53, 53));
//    p.setColor(QPalette::WindowText, Qt::white);
//    p.setColor(QPalette::Base, QColor(25, 25, 25));
//    p.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
//    p.setColor(QPalette::ToolTipBase, Qt::white);
//    p.setColor(QPalette::ToolTipText, Qt::white);
//    p.setColor(QPalette::Text, Qt::white);
//    p.setColor(QPalette::Button, QColor(53, 53, 53));
//    p.setColor(QPalette::ButtonText, Qt::white);
//    p.setColor(QPalette::BrightText, Qt::red);
//    p.setColor(QPalette::Link, QColor(42, 130, 218));
////    p.setColor(QPalette::Highlight, QColor(42, 130, 218));
//    p.setColor(QPalette::Highlight, QColor(142, 45, 197));
//    p.setColor(QPalette::HighlightedText, Qt::black);
//    a.setPalette(p);
//    qDebug() << QStyleFactory::keys();
    MainWindow w;
    w.show();

    return a.exec();
}
