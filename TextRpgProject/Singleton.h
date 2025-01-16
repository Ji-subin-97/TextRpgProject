#pragma once

template <typename T>
class SingleTon
{
private:
	static T* instance;
protected:
	SingleTon() {}
	virtual ~SingleTon() {}
public:
	SingleTon(const SingleTon&) = delete;
	SingleTon& operator=(const SingleTon&) = delete;

	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
		return instance;
	}

	static void DeleteInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

};

template <typename T>
T* SingleTon<T>::instance = nullptr;