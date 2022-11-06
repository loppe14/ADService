#pragma once
#include <memory>
#include <typeinfo>
#include <QtCore>
template<class T>
struct newPolicy
{
	template<typename ...Args>
	static auto make(Args&&...args) ->decltype(new T(std::forward<Args>(args)...))	
	{
		qDebug() << "created " << typeid(T).name();
		return new T(std::forward<Args>(args)...);
	}
};
template<class T>

struct uniquePtrPolicy
{
	template<typename ...Args>
	static auto make(Args&&...args) ->decltype(std::make_unique<T, Args...>(std::forward<Args>(args)...))
	{
		std::make_unique<T, Args...>(std::forward<Args>(args)...);
	}
};
template<class T,template<class>  class Policy>
class ObjFactory 
{
public:
	template<typename ...Args>
	static auto create(Args&&...args) ->decltype(Policy<T>::make(std::forward<Args>(args)...))
	{
		
		return Policy<T>::make(std::forward<Args>(args)...);
	}	
};
template<class T>
using newOpFactory = ObjFactory<T, newPolicy>;
#include "FactotyCreateFunctions.inl"