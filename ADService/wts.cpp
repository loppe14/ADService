#include "wts.h"
int WTS::init(ServersRep*rep)
{
	_rep=rep;
	return 1;
}

ServerList WTS::getServerNames()
{
	ServerList list;
	WTS_SERVER_INFOA** pServerInfo = nullptr;
	DWORD count;
	qDebug() << "Wts start";
	if (!WTSEnumerateServersA(
		nullptr
		, 0, 1, pServerInfo, &count)) 
	{
		qDebug() << "Wts fail";
		return ServerList();
	}
	qDebug() << "Wts work";
	for (size_t i = 0; i < count; i++)
	{
		list.push_back(QString( (*pServerInfo)++->pServerName));
	}
	WTSFreeMemory(pServerInfo);
	return list;
}

WTS::~WTS()
{}
