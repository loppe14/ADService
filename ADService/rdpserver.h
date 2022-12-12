#pragma once

#include <QObject>
#include "idirectoryaccess.h"
#include "wts.h"
#include "singletonHolder.h"
#include "logger.h"
using staticLogger = SingletonHolder<Logger>;
class RDsession : public QObject {
	Q_OBJECT
	enum RDState;
	RDState _state;
	ulong   _id;
	QString _station;
	QString _user;
	QString _server;
public:
	enum  RDState
	{
		Active,
		Connected,
		ConnectQuery,
		Shadow,
		Disconnected,
		Idle,
		Listen,
		Reset,
		Down,
		Init
	};
	Q_ENUM(RDState);
	RDsession(ulong id, const QString& station,const QString& user, const RDState& state,
		const QString& server, QObject* parent = nullptr);
	QString station()  const { return _station; }
	QString user()	   const { return _user; }
	QString StrState() const { return QString(QMetaEnum::fromType<RDState>().valueToKey(_state)); }
	QString server()   const { return _server; }
	RDState state()    const { return _state; }
	ulong   id()       const { return _id; }
};
class RDServer  : public QObject,protected ServerConfig
{
	Q_OBJECT;
	QList<RDsession*> _sessions;
	HANDLE hServer;
public:
	RDServer(const QString& hostname, QObject *parent = nullptr);
	RDServer(const ServerConfig* rep, QObject* parent = nullptr);
	QList<RDsession*> sessions() const;
	~RDServer();
public slots:
	bool updateSessions();
};
