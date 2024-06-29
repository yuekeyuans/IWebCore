#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/config/IConfigManageInterface.h"
#include "core/unit/IStackObjectUnit.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T>
class IConfigImportInterface : public IStackObjectUnit
{
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
    mutable bool m_isFound{false};      // this value is not default value;
    const QString m_path;
    mutable std::atomic_bool m_isLoaded{false};     // this value is loaded value.
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
    if(!m_isFound){
        if(!m_isLoaded){
            auto value  = getConfigManage()->getConfig(m_path);
            if(value.isOk()){
                auto realValue = IJsonUtil::fromJson<T>(value);
                if(realValue.isOk()){
                    m_data = realValue;
                    m_isFound = true;
                }
            }
        }
        m_isLoaded = true;
    }
    return m_data;
}

$PackageWebCoreEnd
