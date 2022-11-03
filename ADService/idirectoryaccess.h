#pragma once
#include "QtCore"
using ServerList = QStringList;
//abstract repository of server names
struct ServersRep
{
	QString _hostname;//domain name
	ServersRep(const QString& hm);
	virtual ~ServersRep();
};
// interface for directory access protocol
class IDirectoryAccess
{
	enum  State;
public:
	virtual ServerList getServerNames() = 0;
	virtual int init(ServersRep* rep) = 0;
	enum  State
	{
		Announced,
		Initialized
	};
protected:
	IDirectoryAccess() =default;
	IDirectoryAccess(const IDirectoryAccess&) = delete;
	IDirectoryAccess& operator=(const IDirectoryAccess&) = delete;
	virtual ~IDirectoryAccess() = 0;
};
class DirectoryAccess : public IDirectoryAccess
{
public:
	State getCurState();
	QString getErrorString();

protected:
	DirectoryAccess(const State& st);
	DirectoryAccess();
	State curState;
	QString errorString;
};