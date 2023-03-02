#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

template<typename T, const char* path>
class IContextImport
{
public:
    IContextImport() = default;
    IContextImport(const T& value);
    ~IContextImport() = default;

public:
    void setValue(T value);
    const T& value() const;

    T& operator =(T value);

    bool operator !=(const T& value) const;
    bool operator <(const T& vlaue) const;
    bool operator >(const T& value) const;

    operator T() const;
//    operator T&() const;

    operator *();

private:
    T& get() const;

private:
    mutable T m_data {};
    mutable std::atomic_bool m_isLoaded{false};
};

template<typename T, const char *path>
IContextImport<T, path>::IContextImport(const T &value)
{
    m_data = value;
}

template<typename T, const char *path>
void IContextImport<T, path>::setValue(T value)
{
    m_data = std::move(value);
}

template<typename T, const char *path>
const T &IContextImport<T, path>::value() const
{
    return get();
}

template<typename T, const char *path>
T &IContextImport<T, path>::operator =(T value)
{
    m_data = value;
    return m_data;
}

template<typename T, const char *path>
bool IContextImport<T, path>::operator !=(const T &value) const
{
    return get() != value;
}

template<typename T, const char *path>
bool IContextImport<T, path>::operator <(const T &value) const
{
    return get() < value;
}

template<typename T, const char *path>
bool IContextImport<T, path>::operator >(const T &value) const
{
    return get() > value;
}

template<typename T, const char *path>
IContextImport<T, path>::operator T() const
{
    return get();
}

//template<typename T, const char *path>
//IContextImport<T, path>::operator T &() const
//{
//    return get();
//}

template<typename T, const char *path>
IContextImport<T, path>::operator *()
{
    return get();
}

template<typename T, const char *path>
T &IContextImport<T, path>::get() const
{
    if(!m_isLoaded){
        bool ok;
        auto value = IContextManage::getApplicationConfig(path, &ok);
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
using ImportInt = IContextImport<int, path>;

$PackageWebCoreEnd
