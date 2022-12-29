#include "qtldap.h"
QtLdap::QtLdap(LdapConfig* conf)
	:_config(conf)
{
}
int QtLdap::init()
{
	auto cleanup = qScopeGuard([=] {unbind(); });
	if (_state != Announced)
		unbind();
	ServerList list;
	if (!ldapInit(_config->hostname(), _config->port()))
	{
		unbind();
		return 0;
	}
	if (!connect())
	{
		unbind();
		return 0;
	}
	if (_config->isUsingSasl()) {
		if (!sasl_bind(_config->dn(), _config->passw()))
		{
			unbind();
			return 0;
		}
	}
	else
	if (!bind(_config->dn(), _config->passw(), _config->auth()))
	{
		unbind();
		return 0;
	}
	_state =Initialized;
	return 1;
}
int QtLdap::getServers(ServerList* list)
{
	QLdapEntryList results;
	QStringList sList;
	if (!search(_config->hostname(), _config->filter(), &results))
	{
		return 0;
	}
	list->clear();
	for (auto i : results)
	{

		for (QLdapEntry::iterator it = i.begin(); it !=i.end(); it++)
		{
			sList.append(it.value());
		}
	}
	*list = sList;
	return 1;
}
QtLdap::~QtLdap() {}

LdapConfig::LdapConfig(const QString& hn, ulong port,
	const QString& dn, const QString& passw,
	BindAuth bAuth, const QString& filt,
	bool sasl)
	: ServerConfig(hn)
	, _port(port)
	, _passw(passw)
	, _dn()
	, _auth(bAuth)
	, _filter(filt)
	, _isUsingSasl(sasl)
{}
LdapConfig::~LdapConfig() {}