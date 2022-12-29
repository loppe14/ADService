#include "appwindow.h"
AbstractAppWindow::AbstractAppWindow(QWidget* parent)
    :QMainWindow(parent)
{
        setModel(new RDSessListModel(this));
}
void AbstractAppWindow::setModel(RDSessListModel* model)
{
    _model = model;
}
RDSessListModel* AbstractAppWindow::getModel() const { return _model; }

MainWindow::MainWindow(QWidget* parent)
    : AbstractAppWindow(parent)
{

    setupUi(this);  
    connect(staticLogger::instance(), &Logger::logged, logSection, &QPlainTextEdit::appendPlainText);
    connect(loadPbt, &QPushButton::clicked, this, &AbstractAppWindow::updateSess);
    connect(actionSwitch_Method, QAction::triggered, &AbstractAppWindow::switchServerReceivingMethod);
    quickView->rootContext()->setContextProperty("sessModel",  _model);
    quickView->setSource(QUrl::fromLocalFile("SessionsView.qml"));

}



