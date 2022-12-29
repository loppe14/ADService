#pragma once
#include <Windows.h>
#include <QObject>
#include <WtsApi32.h>
#include <memory>
#include "rdpserver.h"
#include "serverlogic.h"
#pragma comment(lib, "Wtsapi32.lib")
// qt wrapper over Window terminal serveces
class WTS  : public ServerRep
{
	ServerConfig* _rep;
public:
	WTS(ServerConfig* config = nullptr);
	int getServers(ServerList *list)override;
	int init() override;
	~WTS();
};
