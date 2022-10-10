#pragma once
#include "QtCore"
using ServerList = QList<QString>;
//abstract repository of server names
struct ServersRep {};
// interface for directory access protocol
class IDirectoryAccess
{
	enum  State;
public:
	virtual ServerList getServerNames() = 0;
	virtual int init(ServersRep* rep) = 0;
	virtual QString errorString() const = 0;
	virtual State curState() const = 0;
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
IDirectoryAccess::~IDirectoryAccess() {}