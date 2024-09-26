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
public:
    // 0x01 initialzedValue, 0x02 defaultValue, 0x03 loadedValue;
    struct ValueType {
        ValueType();
        uint valueType : 3;
        bool isLoaded : 1;
        bool isFound  : 1;
    };

protected:
    explicit IConfigImportInterface(std::string path);
    explicit IConfigImportInterface(std::string path, T value);

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

public:
    // TODO: 这里需要改成 enum 么？
    static constexpr inline uint InitializedValue = 0x01;
    static constexpr inline uint DefaultValue = 0x02;
    static constexpr inline uint LoadedValue = 0x04;

protected:
    const std::string m_path;
    mutable T m_data {};
    mutable ValueType m_valueType;

};

template<typename T>
IConfigImportInterface<T>::IConfigImportInterface(std::string path)
    : m_path(std::move(path))
{
    m_valueType.valueType = InitializedValue;
}

template<typename T>
IConfigImportInterface<T>::IConfigImportInterface(std::string path, T value)
    : m_path(std::move(path)), m_data(std::move(value))
{
    m_valueType.valueType = DefaultValue;
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
    return m_valueType.isLoaded;
}

template<typename T>
bool IConfigImportInterface<T>::isFound() const
{
    return m_valueType.isFound;
}

template<typename T>
const QString &IConfigImportInterface<T>::path()
{
    return m_path;
}

// TODO: unfinished
template<typename T>
T &IConfigImportInterface<T>::get() const
{
    if(!m_valueType.isLoaded){
        auto value = getConfigManage()->getConfig(m_path);
        if(value.is_null()){
            m_valueType.isFound = false;
        }

        if constexpr (std::is_same_v<T, IJson>){
            m_data = value;
            m_valueType.isFound = true;
        } else if constexpr (std::is_same_v<T, bool>){
            m_valueType.isFound = value.is_boolean();
            if(m_valueType.isFound){
                m_data = value.get<bool>();
                m_valueType.isFound = true;
            }
        } else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>){
            m_valueType.isFound = value.is_number();
            if(m_valueType.isFound){
                m_data = value.get<int64_t>();
            }
        } else if constexpr (std::is_integral_v<T> && !std::is_signed_v<T>){
            m_valueType.isFound = value.is_number();
            if(m_valueType.isFound){
                m_data = value.get<uint64_t>();
            }
        } else if constexpr (std::is_floating_point_v<T>){
            m_valueType.isFound = value.is_number();
            if(m_valueType.isFound){
                m_data = value.get<double>();
            }
        } else if constexpr (std::is_same_v<std::string, T>){

        } else if constexpr (std::is_same_v<QString, T>){

        } else if constexpr (std::is_same_v<QStringList, T>){

        } else {
            static_assert(true, "not supported config type");
        }

        m_valueType.isLoaded = true;
    }

    return m_data;
}

template<typename T>
IConfigImportInterface<T>::ValueType::ValueType()
{
    memset((void*)this, 0, sizeof(ValueType));
}

$PackageWebCoreEnd
