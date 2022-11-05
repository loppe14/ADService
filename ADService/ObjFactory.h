#pragma once
#include <memory>
template<class T>
class ObjFactory
{
public: 
	static auto create() ->decltype(std::make_unique<T>()) 
	{
		return std::make_unique<T>();
	}
};


#include "FactotyCreateFunctions.inl"