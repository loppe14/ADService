#pragma once
#include "QtCore"
#include "serverlogic.h"
class LdapConfig : public ServerConfig
{
	enum BindAuth;
	ulong    _port;
	QString  _dn;
	QString  _passw;
	BindAuth _auth;
	QString  _filter;
	bool     _isUsingSasl;
public:
	enum BindAuth
	{
		SimpleBind,
		DigestBind
	};
	LdapConfig(const QString&hn,
		ulong port,
		const QString& dn,
		const QString& passw, 
		BindAuth bAuth,
		const QString& filter,
		bool usingSasl);

	ulong port() const { return _port; }
	QString dn() const { return _dn; }
	QString passw()  const { return _passw; }
	BindAuth auth()  const { return _auth; }
	QString filter() const { return _filter; }
	bool    isUsingSasl() const { return _isUsingSasl; }
	~LdapConfig();
};

class QtLdap : public ServerRep
{
public:
	virtual int getServers(ServerList* list) override final;
	int init();

protected:
	LdapConfig* _config;
	using QLdapEntry=QHash<QString, QString>;
	using QLdapEntryList=QList<QLdapEntry>;

	explicit QtLdap(LdapConfig* conf);
	virtual int search(const QString& dn,const QString& filter,QLdapEntryList* searchResults)=0;
	virtual int ldapInit(const QString& url, ulong port)=0;
	virtual int bind(const QString& dn, const QString& passw, LdapConfig::BindAuth authMech)=0;
	virtual int connect(uint connectSec=120, uint connectMsec=0)=0;
	virtual int sasl_bind(const QString&, const QString&)=0;
	virtual int unbind() = 0;

	~QtLdap() = 0;

};