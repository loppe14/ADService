#pragma once
#include <Windows.h>
#include <QObject>
#include <WtsApi32.h>
#include <memory>
#include "idirectoryaccess.h"
#pragma comment(lib, "Wtsapi32.lib")
// qt wrapper over Window terminal serveces
struct RDsession {
	ulong _id;
	RDsession(ulong id):_id(id){}
};
class WTS  : public DirectoryAccess
{
	ServersRep* _rep;
public:
	int init(ServersRep* rep)  override;
	ServerList getServerNames()override;
	~WTS();
};
