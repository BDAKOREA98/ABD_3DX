#pragma once

template <typename T>
class Singleton
{

public:
	
	
	static T* GetInstance();
	static void Dlelte();

protected:

	static T* instance;

};

template <typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
inline T* Singleton<T>::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new T();
	}

	return instance;
}

template<typename T>
inline void Singleton<T>::Dlelte()
{
	if (instance != nullptr)
	{
		delete instance;
	}

}
