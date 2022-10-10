#include "qtldap.h"
QtLdap::QtLdap(QObject* parent/*=nullptr*/) 
	:QObject(parent)
	,_curState(State::Announced) {}

int QtLdap::init(ServersRep* rep)
{
    LdapData* data = (LdapData *)rep;
	if (_curState != Announced)
		release();
	ServerList list; // shared ptr
	if (!init(data->url, data->port)) {
		//when ldap gets an error in derived class it returns 0 and the derived class should fill the errorstring
		release();
		return 0;
	}
	if (bind(data->dn, data->passw, data->auth))
	{
		release();
		return 0;
	}
	_curState =Initialized;
	return 1;
}
IDirectoryAccess::State QtLdap::curState() const{return _curState;}
ServerList QtLdap::getServerNames()
{
	return ServerList();//!!!!!!!!!
}
int QtLdap::release()
{
	unbind();
	_curState = Announced;
}
QtLdap::~QtLdap() {}