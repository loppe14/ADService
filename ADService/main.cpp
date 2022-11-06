#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <qlabel.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* win = new MainWindow;
    win->show();
    return a.exec();
}
