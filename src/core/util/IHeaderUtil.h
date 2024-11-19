#pragma once

#include <QtCore>
#include <QtXml>
#include <QtSql>
#include <IJson.h>
#include <type_traits>
#include "core/util/IPackageUtil.h"
#include "core/base/IStringViewStash.h"
#include "core/base/IStringView.h"
#include <asio.hpp>

#ifndef PP_$_HEADER_UTIL
    Q_DECLARE_METATYPE(std::string)
    #define PP_$_HEADER_UTIL
#endif

$PackageWebCoreBegin

template<typename T, typename ...Args>
T construct(Args...);

$PackageWebCoreEnd
