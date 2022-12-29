
#include "appwindow.h"
#include <QtWidgets/QApplication>
#include "coordinator.h"
#include <qlabel.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
    auto backend = uptrFactory<Coordinator>::create();
    auto mainWindow = uptrFactory<MainWindow>::create();
    backend->setAppWindow(mainWindow.get());
    return a.exec();
}
