#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "ObjFactory.h"
#include <qquickwidget.h>

#include "qqmlapplicationengine.h"
#include "qqmlcomponent.h"
#include "qqmlcontext.h"
#include "rdsessmodel.h" 
class AbstractAppWindow : public QMainWindow
{
    Q_OBJECT
protected:
    RDSessListModel* _model;
    explicit AbstractAppWindow(QWidget* parent = nullptr);
    RDSessListModel* getModel() const;

public:
    void setModel(RDSessListModel*);

signals:
    void updateSess();
    void switchServerReceivingMethod();
    void shadowSession(ulong id, const QString& server);
    void disconnectSession(ulong id, const QString& server);
    void shadowSession(ulong id, const QString* server);

};

class MainWindow : public AbstractAppWindow, public Ui::MainWindowClass
{
public:
    explicit MainWindow( QWidget* parent = nullptr);
    ~MainWindow();
    

};
