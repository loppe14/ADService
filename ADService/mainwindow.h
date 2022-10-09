#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "logger.h"
#include "WinQtLdap.h"
#include "ldapconnectmenu.h"

class MainWindow : public QMainWindow, public Ui::MainWindowClass
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QtLdap* qLdap;
    LdapConnectMenu *cMenu;

public slots:
    void showConnectMenu();
    void LdapBind();
    void LdapConnect();
    void LdapUnbind();

};
