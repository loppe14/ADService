#include "mainwindow.h"
//using LdapSingleton = SingletonHolder<QtLdap, ObjFactory>;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , dAccess(nullptr)
    , sRep(nullptr)
    , logger(ObjFactory<Logger>::create())
    , RDServModel(new QStandardItemModel(this))
{

    setupUi(this);
    connect(actionLdapConnect, &QAction::triggered, this, &MainWindow::initLdapConnection);
    connect(logger, &Logger::logged, logSection, &QPlainTextEdit::appendPlainText);
    connect(actionUserInput, &QAction::triggered, this, &MainWindow::createUserServersInput);
    connect(loadPbt, &QPushButton::clicked, this, &MainWindow::load);
    connect(actionWTS, &QAction::triggered, this, &MainWindow::createWTSconnection);

    UsersTree->setModel(RDServModel);
}


void MainWindow::initLdapConnection() {
    LdapConfig* lData = ObjFactory<LdapConfig>::create();
    LdapConfigMenu* menu = new LdapConfigMenu(lData, this);
    if(menu->exec()==QDialog::Rejected)
        return;
    sRep = lData;
    dAccess = ObjFactory<QtLdap>::create();
    connectToServer();
}
void MainWindow::connectToServer() {  

    logger->log("Connecting to server...");
    if (!dAccess->init(sRep))
    {
        logger->log("error while connecting to server:\n" + dAccess->getErrorString());
    }
    else
    logger->log("successfuly connect to server");
}

void MainWindow::LdapRelease()
{
    QtLdap* qLdap = dynamic_cast<QtLdap*>(dAccess);
    if (qLdap != nullptr)
    {
        qLdap->release();
        qLdap = nullptr;
    }
}
void MainWindow::createUserServersInput()
{
    dAccess = new UserServers(this);
    connectToServer();
}
void MainWindow::createWTSconnection()
{
    dAccess = new WTS;
}
void MainWindow::load()
{
    sList = dAccess->getServerNames();
    if (sList.size() == 0)
    {
        logger->log("error: " + dAccess->getErrorString());
        return;
    }
    logger->log("received servers:");
    for (const QString& str : sList)
    {
        logger->log("    "+str, false);
    }
    RDServModel->clear();
    QStandardItem* root = RDServModel->invisibleRootItem();
    for (const QString& name : sList)
    {   
        logger->log("Connecting to " + name);
        RDServer *serv = new RDServer(name,this);
        logger->log("initialized " + name);
        if (!serv->updateSessions())
        {
            logger->log("error while connecting " + name);
            logger->log(QString::number(GetLastError()));
        }
       
        QStandardItem* item = new QStandardItem(name);
        root->appendRow(item);
        for (RDsession sess : serv->sessions())
        {
            qDebug() << sess._id;
            item->appendRow(new QStandardItem(sess._id));
        }
    }
}

MainWindow::~MainWindow()
{}
