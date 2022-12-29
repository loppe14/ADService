#pragma once

#include <QObject>
#include "logger.h"
#include "appwindow.h"
#include "ObjFactory.h"
#include "rdsessmodel.h"
#include "rdpserver.h"
#include "singletonHolder.h"
#include "servermaster.h"
class Coordinator  : public QObject
{
	Q_OBJECT
private:
	std::unique_ptr<ServerRep> _sRep;
	StaticLogger* _sLogger;
	QHash<QString, RDServer*> _rdServers;
	RDSessListModel *_rdModel;
	AbstractAppWindow* _window;
public:
	void setAppWindow(AbstractAppWindow*);
	Coordinator(QObject *parent = nullptr);
public slots:
	int updateServerRep();
	int updateSessModel();
};
