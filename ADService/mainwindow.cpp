#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , dAccess(nullptr)
    , sRep(nullptr)
{

    setupUi(this);  
    connect(actionLdapConnect, &QAction::triggered, this, &MainWindow::initLdapConnection);
    connect(sLogger->instance(), &Logger::logged, logSection, &QPlainTextEdit::appendPlainText);
    connect(actionUserInput, &QAction::triggered, this, &MainWindow::createUserServersInput);
    connect(loadPbt, &QPushButton::clicked, this, &MainWindow::load);
    connect(actionWTS, &QAction::triggered, this, &MainWindow::createWTSconnection);
    quickView->rootContext()->setContextProperty("sessModel",  &sModel);
    quickView->setSource(QUrl::fromLocalFile("SessionsView.qml"));
}


void MainWindow::initLdapConnection() {
    LdapConfig* lData = newOpFactory<LdapConfig>::create(
        "",389,"",LdapConfig::SimpleBind,"",false
    );
    LdapConfigMenu* menu = newOpFactory<LdapConfigMenu>::create(lData, this);
    if(menu->exec()==QDialog::Rejected)
        return;
    sRep = lData;
    dAccess = uptrFactory<QtLdap>::create();
    connectToServer();
}
void MainWindow::connectToServer() {    
    sLogger->instance()->log("Connecting to");
    if (!dAccess->init(sRep))
    {
        sLogger->instance()->log("error while connecting to server:\n" + dAccess->getErrorString());
    }
    else
    sLogger->instance()->log("successfuly connect to server");
}

void MainWindow::LdapRelease()
{
    QtLdap* qLdap = dynamic_cast<QtLdap*>(dAccess.get());
    if (qLdap != nullptr)
    {
        qLdap->release();
        qLdap = nullptr;
    }
}
void MainWindow::createUserServersInput()
{
    dAccess = uptrFactory<UserServers>::create(this);
    load();
}
void MainWindow::createWTSconnection()
{
    dAccess = uptrFactory<WTS>::create();
}
void MainWindow::load()
{
    if (!dAccess)
        return;
    if (dAccess->getCurState() == DirectoryAccess::Announced)
        connectToServer();
    if (!dAccess->getServerNames(&sList))
    {
        sLogger->instance()->log("Error while while getting servers " + dAccess->getErrorString());
        return;
    }
    sLogger->instance()->log("received servers:");
    for (const QString& str : sList)
    {
        sLogger->instance()->log("    "+str, false);
    }
    for (const QString& name : sList)
    {   
        sLogger->instance()->log("Connecting to " + name);
        RDServer* serv = new RDServer(name);
        
        sLogger->instance()->log("initialized " + name);
        if (!serv->updateSessions())
        {
            sLogger->instance()->log("error while connecting " + name);
            sLogger->instance()->log(QString::number(GetLastError()));
        }
        sModel.setSessionList(serv->sessions(), 0);
    }
    
}

MainWindow::~MainWindow()
{
    DirectoryAccess *p = dAccess.release();
    delete p;
}
