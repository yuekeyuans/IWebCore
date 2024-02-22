#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IResponseWare;

class IResponseManage : public ISingletonUnit<IResponseManage>
{
    friend class ISingletonUnit<IResponseManage>;
private:
    IResponseManage() = default;

public:
    static void registerResponseType(IResponseWare* response);
    static IResponseWare* convertMatch(const QString&);

private:
    QVector<IResponseWare*> responses;     // all response type;
    QVector<IResponseWare*> stringConvertResponses;     // the response that should match the string
};

$PackageWebCoreEnd
