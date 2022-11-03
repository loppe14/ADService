#include "qtldap.h"
QtLdap::QtLdap(QObject* parent/*=nullptr*/) 
	:DirectoryAccess(State::Announced) {}
int QtLdap::init(ServersRep *rep)
{
    config = dynamic_cast<LdapConfig *>(rep);
	if (curState != Announced)
		release();
	ServerList list; // shared ptr
	if (!init(config->_hostname, config->port)) {
		//when ldap gets an error in derived class it returns 0 and the derived class should fill the errorstring
		release();
		return 0;
	}
	if (config->usingSasl) {
		if (!sasl_bind(config->dn, config->passw))
		{
			release();
			return 0;
		}
	}
	if (!bind(config->dn, config->passw, config->auth))
	{
		release();
		return 0;
	}
	curState =Initialized;
	return 1;
}
ServerList QtLdap::getServerNames()
{
	ServerList list;
	QLdapEntryList results;
	if (!search(config->dn, config->filter, &results))
	{
		return ServerList();
	}
	for (auto i : results)
	{

		for (QLdapEntry::iterator it = i.begin(); it !=i.end(); it++)
		{
			list.append(it.value());
		}
	}
	return list;
}
int QtLdap::release()
{
	if (!unbind())
		throw std::logic_error("Ldap unbind error " + getErrorString().toStdString());
	curState = Announced;
	return 1;

}
QtLdap::~QtLdap() {}

LdapConfig::LdapConfig(const QString& hn, ulong port,
	const QString& passw, BindAuth bAuth,
	const QString& filt,
	bool sasl)
	: ServersRep(hn)
	, port(port)
	, passw(passw)
	, auth(bAuth)
	, filter(filt)
	, usingSasl(sasl)
{}
LdapConfig::~LdapConfig() {}