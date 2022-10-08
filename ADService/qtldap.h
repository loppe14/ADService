#pragma once
#include "QtCore"
#ifdef _WIN32
#endif // _WIN32

// directory accses interface
using ServerList = QList<QString>;
class IDirectoryAccess
{
protected:	 
	IDirectoryAccess() = default;
	IDirectoryAccess(const IDirectoryAccess&) = delete;
	IDirectoryAccess& operator=(IDirectoryAccess&) = delete;
	virtual ServerList getServerNames();
	virtual ~IDirectoryAccess() = 0;
};
class QtLdap// : public IDirectoryAccess
{
protected:
	enum State
	{
		Announced,
		Initialized,
		Connected,
		Binded

	};
	enum BindAuth
	{
		SimpleBind,
		DigestBind
	};
	State curState;
	QString errorString;
public:

	explicit QtLdap() = default;
	//virtual ServerList 
	virtual int init(const QString& url, ulong port)=0;
	virtual int bind(const QString& dn, const QString& passw, BindAuth authMech)=0;
	virtual int connect(uint connectSec, uint connectMsec)=0;
	virtual int unbind()=0;
	virtual ~QtLdap();


};