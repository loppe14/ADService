#include "wts.h"
WTS::WTS(ServerConfig*config)
	:_rep(config)
{
}
int WTS::init()
{
	return 1;
}
int WTS::getServers(ServerList*list)
{
	WTS_SERVER_INFOW* pServerInfo = NULL;
	DWORD count;
	if (!WTSEnumerateServersW(
		NULL, 0, 1, &pServerInfo, &count)) 
	{
		_errorString = "WTSEnumerateServersW() error : " +QString::number(GetLastError());
		return 0;
	}
	for (size_t i = 0; i < count; i++)
	{
		list->push_back(newOpFactory<RDServer>::create(QString::fromWCharArray(pServerInfo++->pServerName)));
	}
	//WTSFreeMemory(pServerInfo);
	return 1;
}

WTS::~WTS()
{}
