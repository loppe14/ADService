#pragma once
#pragma comment(lib,"Wldap32.lib")

#include <Winsock2.h>
#include <Windows.h>
#include <Winldap.h>
#include <winber.h>
#include "QtCore"
// LDAP wrapper over Winldap for working with QT 
class QtLdapI : public QObject
{
	enum LdapState;
	enum BindAuth;
protected:
	ldap* pLdap;
	QString errorString;
	LdapState curState;
public:
	explicit QtLdapI(QObject* parent = nullptr);
	QtLdapI(const QtLdapI&) = delete;
	QtLdapI& operator=(QtLdapI&) = delete;
	virtual int init(const QString& url, ULONG port = LDAP_PORT) = 0;
	virtual int bind(const QString& dn, const QString& passw, BindAuth authMech) = 0;
	virtual const QString& error_string();
	virtual int close();
	int handle_lres(ULONG _res, const char* msg);


	enum LdapState {
		Announced,
		Initialized,
		Connected,
		Binded
	};
	enum BindAuth {
		SimpleAuth = LDAP_AUTH_SIMPLE,
		DigestAuth = LDAP_AUTH_DIGEST
	};
	virtual ~QtLdapI() = 0;
};
class QtLdap : public QtLdapI
{
public:
	explicit QtLdap(QObject* parent = nullptr);
	int init(const QString& url, ULONG port = LDAP_PORT) override;
	int bind(const QString& dn, const QString& passw, BindAuth authMech) override;
	~QtLdap() override;
};

//class SecureQtLdap : public QtLdapI
//{
//public:
//	explicit SecureQtLdap(QObject* parent = nullptr);
//	ULONG init(const QString &url, ULONG port) override;
//	ULONG bind(const QString &dn, const QString &passw, const QString &authMech);
//	
//};
