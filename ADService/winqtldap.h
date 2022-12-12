#pragma once
#include <winsock.h>
#include <Windows.h>
#include <Winldap.h>
#include "qtldap.h"
#include <QObject>
#include "logger.h"
#pragma comment(lib, "Wldap32.lib")

class WinQtLdap : public QtLdap
{
	ldap* _pLdap;
public:
	explicit WinQtLdap(QObject *parent =nullptr);
    ~WinQtLdap();
protected:

    int ldapInit(const QString& url, ulong port) override;
    int bind(const QString& dn="", const QString& passw="", LdapConfig::BindAuth authMech=LdapConfig::SimpleBind)override;
    int connect(uint connectSec = 120, uint connectMsec = 0)override;
    int sasl_bind(const QString&, const QString&) override;
    int search(const QString& baseDN, const QString &filter, QLdapEntryList* searchResults)override;
    int unbind()override;
	int handle_res(ulong res, const char* msg);
};
 