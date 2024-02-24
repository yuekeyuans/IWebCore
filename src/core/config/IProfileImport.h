#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/config/IConfigImportInterface.h"
#include "core/config/IProfileManage.h"

$PackageWebCoreBegin

template<typename T>
class IProfileImport : public IConfigImportInterface<T>
{
public:
    IProfileImport(QString path, T value = {});

public:
    IProfileImport& operator =(const T& value);

protected:
    virtual IConfigManageInterface* getConfigManage() const final;
};

template<typename T>
IProfileImport<T>::IProfileImport(QString path, T value) : IConfigImportInterface<T>(path, value)
{
}

// NOTE: 设置值之后，就不会再加载了
template<typename T>
IProfileImport<T>& IProfileImport<T>::operator =(const T& value)
{
    this->m_isLoaded = false;
    this->m_isFound = true;
    this->m_data = value;
    return *this;
}

template<typename T>
IConfigManageInterface *IProfileImport<T>::getConfigManage() const
{
    return IProfileManage::instance();
}

template<typename T>
using $Profile = IProfileImport<T>;

using $ProfileBool = $Profile<bool>;
using $ProfileChar = $Profile<char>;
using $ProfileUChar = $Profile<uchar>;
using $ProfileShort = $Profile<short>;
using $ProfileUShort = $Profile<ushort>;
using $ProfileInt = $Profile<int>;
using $ProfileUInt = $Profile<uint>;
using $ProfileLong = $Profile<long>;
using $ProfileULong = $Profile<ulong>;
using $ProfileLongLong = $Profile<long long>;
using $ProfileULongLong = $Profile<qulonglong>;
using $ProfileFloat = $Profile<float>;
using $ProfileDouble = $Profile<double>;
using $ProfileLongDouble = $Profile<long double>;

using $ProfileQString = $Profile<QString>;

using $Bool = $Profile<bool>;
using $Char = $Profile<char>;
using $UChar = $Profile<uchar>;
using $Short = $Profile<short>;
using $UShort = $Profile<ushort>;
using $Int = $Profile<int>;
using $UInt = $Profile<uint>;
using $Long = $Profile<long>;
using $ULong = $Profile<ulong>;
using $LongLong = $Profile<long long>;
using $ULongLong = $Profile<qulonglong>;
using $Float = $Profile<float>;
using $Double = $Profile<double>;
using $LongDouble = $Profile<long double>;

using $QString = $Profile<QString>;

$PackageWebCoreEnd
