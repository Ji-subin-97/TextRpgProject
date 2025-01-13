#pragma once

// 싱글톤을 상속받은 클래스는 복사연산자 대입연산자 없음

template <typename T>
class Singleton
{
private:
    static T* instance;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
protected:
    //protected : 외부에서는 참조하지 못하고, 파생클래스만 참조할 수 있음
    //private로 하면 파생 클래스는 베이스 클래스를 참조할 수 없어서 생성자 호출이 안됨
    //protected로 상속 받은 파생 클래스는 따로 protected로 지정하지 않아도 자동으로 protected
    Singleton() = default;
public:
    static T* GetInstance();
    static void DeleteInstance();
};

#define BLOCK_CONSTRUCTOR(ClassName)        \
        friend class Singleton<ClassName>;  \
        ClassName() = default;              


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
inline void Singleton<T>::DeleteInstance()
{
    delete instance;
    instance = nullptr;
}