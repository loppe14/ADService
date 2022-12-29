#pragma once
#include "QtCore"
#include "ObjFactory.h"
class ServerConfig
{
	QString _hostname;
public:
	void setHostname(const QString& hostname) { _hostname=hostname; }
	QString hostname() const { return _hostname; };
	ServerConfig(const QString& hm);
	virtual ~ServerConfig();
};
class ServerList : public QList<ServerConfig*>
{
public:
	using QList::QList;
	ServerList(const QStringList& hostnames);
	~ServerList();
};
// interface for directory access protocol
class IServerRep
{
public:
	virtual int getServers(ServerList* list)  =0;
	virtual QStringList getServerNames()      =0;
	virtual int init() = 0;

protected:
	IServerRep() =default;
	IServerRep(const IServerRep&) = delete;
	IServerRep& operator=(const IServerRep&) = delete;
	virtual ~IServerRep() = 0;
};
class ServerRep : public IServerRep
{
public:
	enum  State
	{
		Invalid,
		Announced,
		Initialized
	};
	State   state() const;
	QString errorString() const;
	virtual QStringList getServerNames() override;
	bool isValid() const;
protected:
	explicit ServerRep(const State& st = Initialized);
	State _state;
	QString _errorString;
};