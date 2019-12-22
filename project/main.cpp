#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("fusion"));

    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowFlags(Qt::FramelessWindowHint);
    //w.setWindowOpacity(5);
    w.show();

    return a.exec();
}
