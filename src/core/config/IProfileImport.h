#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/config/IConfigImportInterface.h"
#include "core/config/IProfileManage.h"

$PackageWebCoreBegin

template<typename T>
class IProfileImport : public IConfigImportInterface<T>
{
public:
    IProfileImport(std::string path);
    IProfileImport(std::string path, T value);

public:
    IProfileImport& operator =(const T& value) = delete;

protected:
    virtual IConfigManageInterface* getConfigManage() const final;
};

template<typename T>
IProfileImport<T>::IProfileImport(std::string path)
    : IConfigImportInterface(std::move(path))
{
}

template<typename T>
IProfileImport<T>::IProfileImport(std::string path, T value)
    : IConfigImportInterface<T>(std::move(path), std::move(value))
{
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
using $ProfileSChar = $Profile<signed char>;
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
using $ProfileStdString = $Profile<std::string>;
using $ProfileQStringList = $Profile<QStringList>;

using $Bool = $ProfileBool;
using $Char = $ProfileChar;
using $UChar = $ProfileUChar;
using $SChar = $ProfileSChar;
using $Short = $ProfileShort;
using $UShort = $ProfileUShort;
using $Int = $ProfileInt;
using $UInt = $ProfileUInt;
using $Long = $ProfileLong;
using $ULong = $ProfileULong;
using $LongLong = $ProfileLongLong;
using $ULongLong = $ProfileULongLong;
using $Float = $ProfileFloat;
using $Double = $ProfileDouble;
using $LongDouble = $ProfileLongDouble;

using $QString = $ProfileQString;
using $StdString = $ProfileStdString;
using $QStringList = $ProfileQStringList;

$PackageWebCoreEnd
