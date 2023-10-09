#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IContextWritter
{
private:
    IContextWritter() = delete;
    void* operator new(size_t) = delete;

//public:
//    static void addSystemConfig(const QJsonValue& value, const QString& path="");
//    static void addApplicationConfig(const QJsonValue& value, const QString& path="");

//    static void removeSystemConfig(const QString& path);
//    static void removeApplicationConfig(const QString& path);
};

$PackageWebCoreEnd
