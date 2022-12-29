#include "localhostserv.h"
LocalHostServ::LocalHostServ(){}
int LocalHostServ::getServers(ServerList* list) 
{
	list->clear();
	list->push_back(newOpFactory<ServerConfig>::create(ServerConfig("127.0.0.1")));
	return 1;
}
