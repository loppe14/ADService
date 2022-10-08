#pragma once
#include <winsock.h>
#include <Windows.h>
#include <Winldap.h>
#include <memory>
#include "qtldap.h"
#include <QObject>
#pragma comment(lib, "Wldap32.lib")

class WinQtLdap : public QtLdap, public QObject
{
	ldap* pLdap;
public:
	explicit WinQtLdap();
	virtual int init(const QString& url, ulong port) override;
	virtual int bind(const QString& dn="", const QString& passw="", BindAuth authMech=SimpleBind)override;
	virtual int connect(uint connectSec = 120, uint connectMsec = 0)override;
	virtual int unbind()override;
	int handle_res(ulong res, const char* msg);
	virtual ~WinQtLdap();
};
 