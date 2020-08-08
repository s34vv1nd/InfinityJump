#pragma once
template<typename T>
class Singleton
{
protected:
	Singleton() noexcept = default;

	Singleton(const Singleton&) = delete;

	Singleton& operator=(const Singleton&) = delete;

	virtual ~Singleton() = default; // to silence base class Singleton<T> has a
									// non-virtual destructor [-Weffc++]
	static T * ms_pInstance;

public:
	static T * GetInstance()
	{
		if (ms_pInstance == 0)
			ms_pInstance = new T;
		return ms_pInstance;
	}

	static void DestroyInstance()
	{
		if (ms_pInstance)
		{
			delete ms_pInstance;
			ms_pInstance = 0;
		}
	}

};

template<typename T>
T * Singleton<T>::ms_pInstance = 0;