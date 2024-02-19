#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/config/IConfigImportInterface.h"

$PackageWebCoreBegin

template<typename T>
class IContextImport : public IConfigImportInterface<T>
{
public:
    IContextImport(QString path, T value = {});

public:
    IContextImport& operator =(const T& value);
};

template<typename T>
IContextImport<T>::IContextImport(QString path, T value) : IConfigImportInterface<T>(path, value)
{
}

template<typename T>
IContextImport<T>& IContextImport<T>::operator =(const T& value)
{
    this->m_data = value;
    return *this;
}

template<typename T>
using $Context = IContextImport<T>;

using $ContextBool = $Context<bool>;
using $ContextChar = $Context<char>;
using $ContextUChar = $Context<uchar>;
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
using $ContextQByteArray = $Context<QByteArray>;

$PackageWebCoreEnd
