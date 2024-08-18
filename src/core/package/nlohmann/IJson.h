#pragma once

#include "json.hpp"
#include "core/util/IPackageUtil.h"
#include <iostream>
#include <fstream>

$PackageWebCoreBegin

using IJson = nlohmann::json;

Q_DECLARE_METATYPE(IJson)

namespace detail{
    class IJsonPrivate{
    public:
        IJsonPrivate(){
            qRegisterMetaType<IJson>();
        }
    };
    static IJsonPrivate jsonPrivate;
}

namespace IJsonUtil2
{

}

$PackageWebCoreEnd
