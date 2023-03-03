#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

template<typename T>
class IContextImport
{
public:
    explicit IContextImport(QString path, T value = {});
    ~IContextImport() = default;

public:
    void setValue(T value);
    const T& value() const;

    T& operator =(T value);

    bool operator !=(const T& value) const;
    bool operator <(const T& vlaue) const;
    bool operator >(const T& value) const;

    operator T() const;

    operator *();

private:
    T& get() const;

private:
    mutable T m_data {};
    mutable QString m_path;
    mutable std::atomic_bool m_isLoaded{false};
};

template<typename T>
IContextImport<T>::IContextImport(QString path, T value)
    : m_path(std::move(path)), m_data(std::move(value))
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
//IContextImport<T>::operator T &() const
//{
//    return get();
//}

template<typename T>
IContextImport<T>::operator *()
{
    return get();
}

template<typename T>
T &IContextImport<T>::get() const
{
    if(!m_isLoaded){
        bool ok;
        auto value = IContextManage::getApplicationConfig(m_path, &ok);
        if(ok){
            m_data = {};
            qDebug() << "data is ok" << value;
            m_isLoaded = true;
        }else{
            qDebug() << "fail to load data";
        }
    }

    return m_data;
}

template<const char* path>
using ImportInt = IContextImport<int>;

$PackageWebCoreEnd
