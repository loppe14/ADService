#pragma once

#include <QObject>
#include "userservers.h"
#include "wts.h"
#include "ldapconfigmenu.h"
#include <memory>
#include "localhostserv.h"
#include "ObjFactory.h"
#include "choicerceivingmethod.h"
class ServerRepMaster
{
	std::unique_ptr<ServerRep> _pRep;
	
public:
	enum ReceivingMethod
	{
		NotSelected,
		Unknown,
		Localhost,
		LDAPMethod,
		WTSMethod,
		UserInput
	};
	explicit ServerRepMaster();
	static std::unique_ptr<ServerRep> getRep(ReceivingMethod m=Unknown);
	virtual ~ServerRepMaster();
};
