#pragma once

#include "json.hpp"
#include "core/util/IPackageUtil.h"
#include <iostream>
#include <fstream>

$PackageWebCoreBegin

using IJson = nlohmann::json;

Q_DECLARE_METATYPE(IJson)
Q_DECLARE_METATYPE(std::string)

namespace detail{
    class IDefaultRegisterType{
    public:
        IDefaultRegisterType(){
            qRegisterMetaType<IJson>();
            qRegisterMetaType<std::string>();
        }
    };
    static IDefaultRegisterType s_type;
}

namespace IJsonUtil2
{

}

$PackageWebCoreEnd
