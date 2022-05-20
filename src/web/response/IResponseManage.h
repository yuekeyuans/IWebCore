#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IResponseWare;

class IResponseManage
{
    $UseInstance(IResponseManage)
public:
    IResponseManage();
    static void registerResponseType(IResponseWare* response);
    static IResponseWare* convertMatch(const QString&);

private:
    QVector<IResponseWare*> responses;     // all response type;
    QVector<IResponseWare*> stringConvertResponses;     // the response that should match the string
};

$PackageWebCoreEnd
