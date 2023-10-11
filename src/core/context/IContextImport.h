#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

template<typename T>
class IContextImport
{
    Q_DISABLE_COPY_MOVE(IContextImport)
public:
    explicit IContextImport(QString path, T value = {});
    ~IContextImport() = default;

public:
    void setValue(T value);
    const T& value() const;

public:
    T& operator =(T value);
    bool operator !=(const T& value) const;
    bool operator <(const T& vlaue) const;
    bool operator >(const T& value) const;
    operator T() const;
//    operator *();

private:    // only run  in stack
    void* operator new[] (std::size_t size) = delete;
    void* operator new[] (std::size_t size, const std::nothrow_t& nothrow_value) = delete;
    void* operator new[] (std::size_t size, void* ptr) = delete;
    void* operator new(std::size_t) = delete;
    void* operator new(std::size_t, void*) = delete;
    void* operator new (std::size_t size, const std::nothrow_t& nothrow_value) throw() = delete;

    void operator delete[] (void* ptr) throw() = delete;
    void operator delete[] (void* ptr, const std::nothrow_t& nothrow_constant) throw() = delete;
    void operator delete[] (void* ptr, void* voidptr2) throw() = delete;
    void operator delete( void * ) = delete;
    void operator delete( void *, size_t ) = delete;

private:
    T& get() const;

private:
    mutable T m_data {};
    mutable std::atomic_bool m_isLoaded{false};
    const QString m_path;
};

template<typename T>
IContextImport<T>::IContextImport(QString path, T value)
    :  m_data(std::move(value)), m_path(std::move(path))
{
}

template<typename T>
void IContextImport<T>::setValue(T value)
{
    m_data = std::move(value);
}

template<typename T>
const T &IContextImport<T>::value() const
{
    return get();
}

template<typename T>
T &IContextImport<T>::operator =(T value)
{
    m_data = value;
    return m_data;
}

template<typename T>
bool IContextImport<T>::operator !=(const T &value) const
{
    return get() != value;
}

template<typename T>
bool IContextImport<T>::operator <(const T &value) const
{
    return get() < value;
}

template<typename T>
bool IContextImport<T>::operator >(const T &value) const
{
    return get() > value;
}

template<typename T>
IContextImport<T>::operator T() const
{
    return get();
}

//template<typename T>
//IContextImport<T>::operator *()
//{
//    return get();
//}

template<typename T>
T &IContextImport<T>::get() const
{
    if(!m_isLoaded){
        bool ok;
        auto value = IContextManage::getApplicationConfig(m_path, &ok);
        if(ok){
            m_data = IJsonUtil::fromJson<T>(value, &ok);
            qDebug() << "data is ok" << value;
        }else{
            qDebug() << "fail to load data" << m_path;
        }
        m_isLoaded = true;
    }

    return m_data;
}

//using $Char = IContextImport<char>;
//using $UChar = IContextImport<uchar>;
using $Short = IContextImport<short>;
using $UShort = IContextImport<ushort>;
using $Int = IContextImport<int>;
using $UInt = IContextImport<uint>;
using $Long = IContextImport<long>;
using $ULong = IContextImport<ulong>;
using $LongLong = IContextImport<long long>;
using $ULongLong = IContextImport<qulonglong>;
using $Float = IContextImport<float>;
using $Double = IContextImport<double>;
using $LongDouble = IContextImport<long double>;

using $Bool = IContextImport<bool>;
using $QString = IContextImport<QString>;

$PackageWebCoreEnd
