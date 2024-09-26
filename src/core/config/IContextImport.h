#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IConfigImportInterface.h"
#include "core/config/IContextManage.h"

$PackageWebCoreBegin

template<typename T>
class IContextImport : public IConfigImportInterface<T>
{
public:
    IContextImport(std::string path);
    IContextImport(std::string path, T value);

public:
    IContextImport& operator=(const T& value) = delete;

protected:
    virtual IConfigManageInterface* getConfigManage() const final;
};

template<typename T>
IContextImport<T>::IContextImport(std::string path)
    : IConfigImportInterface<T>(std::move(path))
{
}

template<typename T>
IContextImport<T>::IContextImport(std::string path, T value)
    : IConfigImportInterface<T>(std::move(path), std::move(value))
{
}

template<typename T>
IConfigManageInterface *IContextImport<T>::getConfigManage() const
{
    return IContextManage::instance();
}

template<typename T>
using $Context = IContextImport<T>;

using $ContextBool = $Context<bool>;
using $ContextChar = $Context<char>;
using $ContextUChar = $Context<uchar>;
using $ContextSChar = $Context<signed char>;
using $ContextShort = $Context<short>;
using $ContextUShort = $Context<ushort>;
using $ContextInt = $Context<int>;
using $ContextUInt = $Context<uint>;
using $ContextLong = $Context<long>;
using $ContextULong = $Context<ulong>;
using $ContextLongLong = $Context<long long>;
using $ContextULongLong = $Context<qulonglong>;
using $ContextFloat = $Context<float>;
using $ContextDouble = $Context<double>;
using $ContextLongDouble = $Context<long double>;

using $ContextQString = $Context<QString>;
using $ContextStdString = $Context<std::string>;
using $ContextQStringList = $Context<QStringList>;

$PackageWebCoreEnd
