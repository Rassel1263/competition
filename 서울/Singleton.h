#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	Singleton(const T&) = delete;
	Singleton operator = (const T&) = delete;

public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
};
