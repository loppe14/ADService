#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "logger.h"
#include "WinQtLdap.h"
#include "singletonHolder.h"
#include "ObjFactory.h"
#include "ldapconfigmenu.h"
#include "QStandardItemModel"
#include "rdpserver.h"
#include <memory>
#include "userservers.h"
#include "wts.h"

class MainWindow : public QMainWindow, public Ui::MainWindowClass
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    DirectoryAccess* dAccess;
    ServerList sList;
    ServersRep* sRep;
    Logger* logger;
    QStandardItemModel *RDServModel;
public slots:
    void initLdapConnection();
    void createUserServersInput();
    void createWTSconnection();
    void load();
    void connectToServer();
    void LdapRelease();

};
