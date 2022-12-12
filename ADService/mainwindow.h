#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "logger.h"
#include "WinQtLdap.h"
#include "ObjFactory.h"
#include "ldapconfigmenu.h"
#include "rdsessmodel.h"
#include <qquickwidget.h>
#include "QStandardItemModel"
#include "qqmlapplicationengine.h"
#include "rdpserver.h"
#include "qqmlcomponent.h"
#include "qqmlcontext.h"
#include "userservers.h"
#include "wts.h"
#include "singletonHolder.h"
using staticLogger = SingletonHolder<Logger>;

class MainWindow : public QMainWindow, public Ui::MainWindowClass
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<DirectoryAccess> dAccess;
    ServerList sList;
    ServerConfig* sRep;
    staticLogger* sLogger;
    RDSessListModel sModel = RDSessListModel();
public slots:
    void initLdapConnection();
    void createUserServersInput();
    void createWTSconnection();
    void load();
    void connectToServer();
    void LdapRelease();
};
