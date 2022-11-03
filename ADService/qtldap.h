#pragma once
#include "QtCore"
#include "idirectoryaccess.h"
struct LdapConfig : public ServersRep
{
	enum BindAuth;
	ulong    port;
	QString  dn;
	QString  passw;
	BindAuth auth;
	QString filter;
	bool usingSasl;
	enum BindAuth
	{
		SimpleBind,
		DigestBind
	};
	LdapConfig(const QString&hn,
		ulong port,
		const QString& passw, 
		BindAuth bAuth,
		const QString& filter,
		bool usingSasl);
	~LdapConfig();
};

class QtLdap : public DirectoryAccess
{
	LdapConfig* config;
public:
	ServerList getServerNames() override final;
	int init(ServersRep *)		override final;
	int release();

protected:
	using QLdapEntry=QHash<QString, QString>;
	using QLdapEntryList=QList<QLdapEntry>;

	explicit QtLdap(QObject* parent = nullptr);
	virtual int search(const QString& dn,const QString& filter,QLdapEntryList* searchResults)=0;
	virtual int init(const QString& url, ulong port)=0;
	virtual int bind(const QString& dn, const QString& passw, LdapConfig::BindAuth authMech)=0;
	virtual int connect(uint connectSec, uint connectMsec)=0;
	virtual int sasl_bind(const QString&, const QString&)=0;
	virtual int unbind() = 0;
	~QtLdap() = 0;

};