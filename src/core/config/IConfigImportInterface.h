#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/config/IConfigManageInterface.h"
#include "core/unit/IStackObjectUnit.h"

$PackageWebCoreBegin

template<typename T>
class IConfigImportInterface : public IStackObjectUnit
{
    Q_DISABLE_COPY_MOVE(IConfigImportInterface)
protected:
    explicit IConfigImportInterface(QString path, T value);

public:
    bool operator !=(const T& value) const;
    operator const T&() const;
    const T& value() const;

public:
    bool isLoaded() const;
    bool isFound() const;
    const QString& path();

protected:
    virtual IConfigManageInterface* getConfigManage() const = 0;

private:
    T& get() const;

protected:
    mutable T m_data {};

private:
    mutable bool m_isFound{false};
    const QString m_path;
    mutable std::atomic_bool m_isLoaded{false};
};

template<typename T>
IConfigImportInterface<T>::IConfigImportInterface(QString path, T value)
    :  m_data(std::move(value)), m_path(std::move(path))
{
}

template<typename T>
bool IConfigImportInterface<T>::operator !=(const T &value) const
{
    return get() != value;
}

template<typename T>
IConfigImportInterface<T>::operator const T&() const
{
    return get();
}

template<typename T>
const T &IConfigImportInterface<T>::value() const
{
    return get();
}

template<typename T>
bool IConfigImportInterface<T>::isLoaded() const
{
    return m_isLoaded;
}

template<typename T>
bool IConfigImportInterface<T>::isFound() const
{
    if(!m_isLoaded){    // lazy load
        value();
    }

    return m_isFound;
}

template<typename T>
const QString &IConfigImportInterface<T>::path()
{
    return m_path;
}

template<typename T>
T &IConfigImportInterface<T>::get() const
{
   if(!m_isLoaded){
       auto value = getConfigManage()->getConfig(m_path, &m_isFound);
       if(m_isFound){
           m_data = IJsonUtil::fromJson<T>(value, &m_isFound);
       }
       m_isLoaded = true;
   }

    return m_data;
}

$PackageWebCoreEnd
