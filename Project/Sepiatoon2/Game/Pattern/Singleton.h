#pragma once

template<class T>
class Singleton
{
public:
	static T* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}
	static void deleteInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
private:
	static T* instance;
};

