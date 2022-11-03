#include "wts.h"
int WTS::init(ServersRep*rep)
{
	_rep=rep;
	return 1;
}

ServerList WTS::getServerNames()
{
	ServerList list;
	WTS_SERVER_INFOA** pServerInfo = NULL;
	DWORD count;
	qDebug() << "start";
	if (!WTSEnumerateServersA(/*(LPWSTR)_rep->_hostname.toStdWString().c_str()*/
		NULL
		, 0, 1, pServerInfo, &count)) 
	{
		qDebug() << "fail";
		return ServerList();
	}
	qDebug() << "work";
	for (size_t i = 0; i < count; i++)
	{
		list.push_back(QString( (*pServerInfo)++->pServerName));
	}
	WTSFreeMemory(pServerInfo);
	return list;
}

WTS::~WTS()
{}