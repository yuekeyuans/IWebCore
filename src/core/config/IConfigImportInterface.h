#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/config/IContextManage.h"

$PackageWebCoreBegin

template<typename T>
class IConfigImportInterface
{
    Q_DISABLE_COPY_MOVE(IConfigImportInterface)
public:
    explicit IConfigImportInterface(QString path, T value = {});
    ~IConfigImportInterface() = default;

public:
    void setValue(T value);
    const T& value() const;

public:
    T& operator =(T value);
    bool operator !=(const T& value) const;
    // bool operator <(const T& vlaue) const;
    // bool operator >(const T& value) const;
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
IConfigImportInterface<T>::IConfigImportInterface(QString path, T value)
    :  m_data(std::move(value)), m_path(std::move(path))
{
}

template<typename T>
void IConfigImportInterface<T>::setValue(T value)
{
    m_data = std::move(value);
}

template<typename T>
const T &IConfigImportInterface<T>::value() const
{
    return get();
}

template<typename T>
T &IConfigImportInterface<T>::operator =(T value)
{
    m_data = value;
    return m_data;
}

template<typename T>
bool IConfigImportInterface<T>::operator !=(const T &value) const
{
    return get() != value;
}

// template<typename T>
// bool IConfigImportInterface<T>::operator <(const T &value) const
// {
//     return get() < value;
// }

// template<typename T>
// bool IConfigImportInterface<T>::operator >(const T &value) const
// {
//     return get() > value;
// }

template<typename T>
IConfigImportInterface<T>::operator T() const
{
    return get();
}

template<typename T>
T &IConfigImportInterface<T>::get() const
{
   if(!m_isLoaded){
       bool ok;
       auto value = IContextManageInstance->getConfig(m_path, &ok);
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

using $Char = IConfigImportInterface<char>;
using $UChar = IConfigImportInterface<uchar>;
using $Short = IConfigImportInterface<short>;
using $UShort = IConfigImportInterface<ushort>;
using $Int = IConfigImportInterface<int>;
using $UInt = IConfigImportInterface<uint>;
using $Long = IConfigImportInterface<long>;
using $ULong = IConfigImportInterface<ulong>;
using $LongLong = IConfigImportInterface<long long>;
using $ULongLong = IConfigImportInterface<qulonglong>;
using $Float = IConfigImportInterface<float>;
using $Double = IConfigImportInterface<double>;
using $LongDouble = IConfigImportInterface<long double>;

using $Bool = IConfigImportInterface<bool>;
using $QString = IConfigImportInterface<QString>;

$PackageWebCoreEnd
