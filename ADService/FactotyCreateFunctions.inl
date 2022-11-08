#pragma once
#include "ObjFactory.h"
#include "winqtldap.h"
#include "logger.h"
#include "qtldap.h"
#include <memory>
template<template<class> class Policy>
class ObjFactory<QtLdap,Policy>
{
public:
	template<typename ...Args>
	static auto create(Args&&...args) 	{
#ifdef WIN32

		return Policy<WinQtLdap>::make(std::forward<Args>(args)...);
		//elseif ... linux needs openldap implementation 
		
	#endif 
		
	}
};