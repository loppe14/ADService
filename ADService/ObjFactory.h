#pragma once
template<class T>
class ObjFactory
{
public: 
	static T* create() {
		return new T;
	}
};


#include "FactotyCreateFunctions.inl"