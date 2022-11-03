#pragma once

#include <QObject>
#include "idirectoryaccess.h"
#include "wts.h"
class RDServer  : public QObject,protected ServersRep
{
	Q_OBJECT;
	QVector<RDsession> _sessions;
	HANDLE hServer;
public:
	RDServer(const QString& hostname, QObject *parent = nullptr);
	RDServer(const ServersRep* rep, QObject* parent = nullptr);
	QVector<RDsession> sessions();
	~RDServer();
public slots:
	bool updateSessions();
};
