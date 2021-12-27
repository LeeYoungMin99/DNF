#pragma once

template <typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;
	virtual ~Singleton() = default;

	static T* GetSingleton()
	{
		static T instance;

		return &instance;
	}
protected:
	Singleton()  = default;
};