#pragma once

#include "core/util/IMetaUtil.h"

$PackageWebCoreBegin

template<typename T>
struct IClassNameUnit
{
    static const std::string CLASS_NAME;
};

template<typename T>
const std::string IClassNameUnit<T>::CLASS_NAME = IMetaUtil::getBareTypeName<T>().toStdString();

$PackageWebCoreEnd
