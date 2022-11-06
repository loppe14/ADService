#pragma once
#include <memory>

template<class T>
struct newPolicy
{
	template<typename ...Args>
	static auto make(Args&&...args) ->decltype(new T(std::forward<Args>(args)...))	
	{
		return new T(std::forward<Args>(args)...);
	}
};
template <class T>
struct uniquePtrPolicy
{
	template<typename ...Args>
	static auto make(Args&&...args) ->decltype(std::make_unique<T, Args...>(std::forward<Args>(args)...))
	{
		std::make_unique<T, Args...>(std::forward<Args>(args)...);
	}
};
template<template<class T> class Policy>
class ObjFactory
{
public: 
	template<typename ...Args>
	static auto create(Args&&...args) ->decltype(Policy::make(std::forward<Args>(args)...))
	{
		return Policy::make(std::forward<Args>(args)...);
	}
};


#include "FactotyCreateFunctions.inl"