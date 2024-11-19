#pragma once

#include "core/util/IMetaUtil.h"

$PackageWebCoreBegin

template<typename T>
struct IClassNameUnit
{
    static const QString CLASS_NAME;
};

template<typename T>
const QString IClassNameUnit<T>::CLASS_NAME = IMetaUtil::getBareTypeName<T>();

$PackageWebCoreEnd
