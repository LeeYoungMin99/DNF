#pragma once

template <typename T>
class Singleton
{
public:
	virtual ~Singleton() = default;

	static T* GetSingleton()
	{
		static T instance;

		return &instance;
	}
protected:
	Singleton() {}
};