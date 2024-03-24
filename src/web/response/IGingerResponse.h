#pragma once

#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IGingerResponse : public IResponseInterface<IGingerResponse>
{
    $AsResponse(IGingerResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IGingerResponse();
//    IGingerResponse(const QString& path, QVariantMap args = {});
    IGingerResponse(const QString& path, QJsonObject args = {});
//    IGingerResponse(const QString& path, std::map<std::string, ginger::object> args);

public:
    virtual QString getPrefixMatcher() final;

};

IGingerResponse operator"" _ginger(const char* str, size_t size);

$PackageWebCoreEnd
