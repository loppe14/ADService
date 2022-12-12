#pragma once
#include "QtCore"
using ServerList = QStringList;
struct ServerConfig
{
	QString _hostname;
	ServerConfig(const QString& hm);
	virtual ~ServerConfig();
};
// interface for directory access protocol
class IDirectoryAccess
{
	enum  State;
public:
	virtual int getServerNames(ServerList* list) = 0;
	virtual int init(ServerConfig* rep) = 0;
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
	State   getCurState()    const;
	QString getErrorString() const;
	QString getHostname()    const;
protected:
	DirectoryAccess(const State& st);
	DirectoryAccess();
	ServerConfig* _config;
	State _curState;
	QString _errorString;
};