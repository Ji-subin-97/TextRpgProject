#pragma once

// �̱����� ��ӹ��� Ŭ������ ���翬���� ���Կ����� ����

template <typename T>
class Singleton
{
private:
    static T* instance;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
protected:
    //protected : �ܺο����� �������� ���ϰ�, �Ļ�Ŭ������ ������ �� ����
    //private�� �ϸ� �Ļ� Ŭ������ ���̽� Ŭ������ ������ �� ��� ������ ȣ���� �ȵ�
    //protected�� ��� ���� �Ļ� Ŭ������ ���� protected�� �������� �ʾƵ� �ڵ����� protected
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