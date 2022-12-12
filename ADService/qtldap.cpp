#include "qtldap.h"
QtLdap::QtLdap(QObject* parent/*=nullptr*/) 
	:DirectoryAccess(State::Announced) {}
int QtLdap::init(ServerConfig *rep)
{
	auto cleanup = qScopeGuard([=] {release(); });
	config = dynamic_cast<LdapConfig *>(rep);
	if (_curState != Announced)
		release();
	ServerList list; // shared ptr
	if (!ldapInit(config->_hostname, config->port)) {
		//when ldap gets an error in derived class it returns 0 and the derived class should fill the errorstring
		return 0;
	}

	if (!connect())
	{
		return 0;
	} 
	if (config->usingSasl) {
		if (!sasl_bind(config->dn, config->passw))
		{
			return 0;
		}
	}
	else
	/*if (!bind(config->dn, config->passw, config->auth))
	{
		return 0;
	}*/
	_curState =Initialized;
	return 1;
}
int QtLdap::getServerNames(ServerList * list)
{
	QLdapEntryList results;
	if (!search(config->_hostname, config->filter, &results))
	{
		return 0;
	}
	for (auto i : results)
	{

		for (QLdapEntry::iterator it = i.begin(); it !=i.end(); it++)
		{
			list->append(it.value());
		}
	}
	return 1;
}
int QtLdap::release()
{
	if (!unbind())
		throw std::logic_error("Ldap unbind error");
	_curState = Announced;
	return 1;

}
QtLdap::~QtLdap() {}

LdapConfig::LdapConfig(const QString& hn, ulong port,
	const QString& passw, BindAuth bAuth,
	const QString& filt,
	bool sasl)
	: ServerConfig(hn)
	, port(port)
	, passw(passw)
	, auth(bAuth)
	, filter(filt)
	, usingSasl(sasl)
{}
LdapConfig::~LdapConfig() {}