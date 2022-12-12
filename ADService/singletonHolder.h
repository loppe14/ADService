#pragma once
#include "ObjFactory.h"
template<class T>
class SingletonHolder
{
	inline static T* ptr=nullptr;
public:
	static T* instance() {
		if (!ptr)
			ptr =newOpFactory<T>::create();
		return ptr;
	}
    T* operator->() const 
	{
		return instance();
	}
};