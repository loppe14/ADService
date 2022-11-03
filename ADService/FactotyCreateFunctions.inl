#pragma once
#include "ObjFactory.h"
#include "winqtldap.h"
#include "logger.h"
#include "qtldap.h"
template<>
class ObjFactory<QtLdap>
{
public:
	static QtLdap* create()
	{
	#ifdef WIN32
				 return new WinQtLdap;
	//linux needs openldap implementation 
		
	#endif 
		
	}
};

template<>
class ObjFactory<LdapConfig>
{
public:
	static LdapConfig* create()
	{
		return new LdapConfig("", 389, "", LdapConfig::SimpleBind, "", false);
	}
};

//QtLdap* ObjFactory::create<QtLdap>()
//	{
//#ifdef WIN32
//		 return new WinQtLdap;
////linux needs openldap implementation 
//
//#endif 
//
//}
