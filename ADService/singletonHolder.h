#pragma once
template<class T, class Factory>
class SingletonHolder
{
	inline static T* ptr=nullptr;
public:
	static T* instance() {
		if (!ptr)
			ptr = Factory<T>::create();
		return ptr;
	}
};