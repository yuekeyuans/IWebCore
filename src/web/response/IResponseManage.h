#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IResponseWare;

class IResponseManage : public ISingletonUnit<IResponseManage>
{
public:
    IResponseManage() = default;

public:
    void registerResponseType(IResponseWare* response);
    IResponseWare* convertMatch(const QString&);

private:
    QVector<IResponseWare*> m_responses;     // all response type;
    QMap<QString, IResponseWare*> stringConvertResponses;
//    QVector<IResponseWare*> stringConvertResponses;     // the response that should match the string
};

$PackageWebCoreEnd
