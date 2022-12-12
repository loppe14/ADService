#pragma once
#include <Windows.h>
#include <QObject>
#include <WtsApi32.h>
#include <memory>
#include "idirectoryaccess.h"
#pragma comment(lib, "Wtsapi32.lib")
// qt wrapper over Window terminal serveces
class WTS  : public DirectoryAccess
{
	ServerConfig* _rep;
public:
	int init(ServerConfig* rep)  override;
	int getServerNames(ServerList *)override;
	~WTS();
};
