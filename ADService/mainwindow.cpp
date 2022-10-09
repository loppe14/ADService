#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , qLdap(new WinQtLdap)

{

    setupUi(this);
    connect(actionConnect, &QAction::triggered,this, &MainWindow::showConnectMenu);
}
void MainWindow::showConnectMenu()
{
    cMenu = new LdapConnectMenu;
    qDebug()<<cMenu;
    cMenu->show();
}
void MainWindow::LdapBind()
{
    
}

void MainWindow::LdapConnect()
{
   // LdapConnectMenu* dial = new LdapConnectMenu(this);
    //dial->exec();
}

void MainWindow::LdapUnbind()
{

}


MainWindow::~MainWindow()
{}
