#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/config/IConfigManageInterface.h"

$PackageWebCoreBegin

template<typename T>
class IConfigImportInterface
{
    Q_DISABLE_COPY_MOVE(IConfigImportInterface)
protected:
    explicit IConfigImportInterface(QString path, T value);

public:
    bool operator !=(const T& value) const;
    operator const T&() const;
    const T& value() const;

public:
    bool isFound() const;

protected:
    virtual IConfigManageInterface* getConfigManage() const = 0;

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
bool IConfigImportInterface<T>::isFound() const
{
    if(!m_isLoaded){    // lazy load
        value();
    }

    return m_isFound;
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
