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
    enum class ValueType : uint8_t{
        InitializedValue,
        DefaultValue,
        LoadedValue         // Note: this will be judged by isLoaded and isFound
    };
    struct ValueMark{
        ValueType valueType{ValueType::InitializedValue};
        bool isLoaded{false};
        bool isFound {false};
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

protected:
    const std::string m_path;
    mutable T m_data {};
    mutable ValueMark m_valueMark{};

};

template<typename T>
IConfigImportInterface<T>::IConfigImportInterface(std::string path)
    : m_path(std::move(path))
{
}

template<typename T>
IConfigImportInterface<T>::IConfigImportInterface(std::string path, T value)
    : m_path(std::move(path)), m_data(std::move(value))
{
    m_valueMark.valueType = ValueType::DefaultValue;
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
    return m_valueMark.isLoaded;
}

template<typename T>
bool IConfigImportInterface<T>::isFound() const
{
    return m_valueMark.isFound;
}

template<typename T>
const QString &IConfigImportInterface<T>::path()
{
    return m_path;
}

template<typename T>
T &IConfigImportInterface<T>::get() const
{
    if(m_valueMark.isLoaded){
        return m_data;
    }
    auto value = getConfigManage()->getConfig(m_path);
    if(value.is_null()){
        m_valueMark.isFound = false;
        return m_data;
    }
    // IJson
    if constexpr (std::is_same_v<T, IJson>){
        m_valueMark.isFound = true;
        m_data = value;
    }
    // bool
    else if constexpr (std::is_same_v<T, bool>){
        m_valueMark.isFound = value.is_boolean();
        if(m_valueMark.isFound){
            m_valueMark.isFound = true;
            m_data = value.get<bool>();
        }
    }

    // signed
    else if constexpr (std::is_integral_v<T> && std::is_signed_v<T>){
        m_valueMark.isFound = value.is_number();
        if(m_valueMark.isFound){
            m_data = value.get<int64_t>();
        }
    }
    // unsigned
    else if constexpr (std::is_integral_v<T> && !std::is_signed_v<T>){
        m_valueMark.isFound = value.is_number();
        if(m_valueMark.isFound){
            m_data = value.get<uint64_t>();
        }
    }
    // floating point
    else if constexpr (std::is_floating_point_v<T>){
        m_valueMark.isFound = value.is_number();
        if(m_valueMark.isFound){
            m_data = value.get<double>();
        }
    }
    // std::string
    else if constexpr (std::is_same_v<std::string, T>){
        m_valueMark.isFound = value.is_string();
        if(m_valueMark.isFound){
            m_data = value.get<std::string>();
        }
    }
    // QString
    else if constexpr (std::is_same_v<QString, T>){
        m_valueMark.isFound = value.is_string();
        if(m_valueMark.isFound){
            m_data = QString::fromStdString(value.get<std::string>());
        }
    }
    // QStringList
    else if constexpr (std::is_same_v<QStringList, T>){
        auto found = value.is_array();
        if(found){
            for(const auto& val : value){
                if(val.is_string()){
                    m_data.append(QString::fromStdString(val.get<std::string>()));
                }else{
                    qFatal("error, not all value are string");
                }
            }
            m_valueMark.isFound = true;
        }
    }

    // not supported
    else{
        static_assert(true, "not supported Config type");
    }

    return m_data;
}

$PackageWebCoreEnd
