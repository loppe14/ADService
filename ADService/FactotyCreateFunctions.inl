#pragma once
#include "ObjFactory.h"
#include "winqtldap.h"
#include "logger.h"
#include "qtldap.h"
#include <memory>
template<>
class ObjFactory<QtLdap>
{
public:
	static std::unique_ptr<QtLdap> create()
	{
	#ifdef WIN32
		return std::make_unique<WinQtLdap>();
	//linux needs openldap implementation 
		
	#endif 
		
	}
};

template<>
class ObjFactory<LdapConfig>
{
public:
	static std::unique_ptr<LdapConfig> create()
	{
		return std::make_unique<LdapConfig>("", 389, "", LdapConfig::SimpleBind, "", false);
	}
};