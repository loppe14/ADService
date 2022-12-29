#include "serverlogic.h"
IServerRep::~IServerRep() {}

ServerConfig::ServerConfig(const QString &hn)
	:_hostname(hn)
{}
ServerConfig::~ServerConfig() {}
ServerList::~ServerList()
{
	while (!isEmpty())
		delete takeFirst();
}
ServerList::ServerList(const QStringList& hostnames)
{
	for (auto& i : hostnames)
	{
		push_back(newOpFactory<ServerConfig>::create(i));
	}
}

ServerRep::ServerRep(const State& st) : _state(st) {}
bool ServerRep::isValid() const { return _state != Invalid; }
QString ServerRep::errorString() const {return _errorString;}
ServerRep::State ServerRep::state() const {return _state;}
QStringList ServerRep::getServerNames()
{
	ServerList list;
	QStringList out;
	if (getServers(&list))
	{
		for (auto& i : list)
		{
			out.push_back(i->hostname());
		}
		return out;
	}
	return QStringList();
}