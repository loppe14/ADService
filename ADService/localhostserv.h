#pragma once
#include "serverlogic.h"
class LocalHostServ : public ServerRep 
{
public:
	LocalHostServ();
	int init() override;
	virtual int getServers(ServerList* list) override;

};

