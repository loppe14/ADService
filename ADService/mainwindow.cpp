#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , dAccess(nullptr)
    , sRep(nullptr)
    , logger(newOpFactory<Logger>::create(this))
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
    connectToServer();
}
void MainWindow::createWTSconnection()
{
    dAccess = uptrFactory<WTS>::create();
}
void MainWindow::load()
{
    if (!dAccess|| dAccess->getCurState() != DirectoryAccess::Initialized)
        return;
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
        RDServer *serv = newOpFactory<RDServer>::create(name,this);
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
            qDebug() <<"sess :"<< sess._id;
            item->appendRow(new QStandardItem(sess._id));
        }
    }
}

MainWindow::~MainWindow()
{}
