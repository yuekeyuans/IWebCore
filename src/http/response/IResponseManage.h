#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class IResponseWare;
class IResponseTemplateRenderer;
class IResponseManage : public ISingletonUnit<IResponseManage>
{
public:
    IResponseManage() = default;

public:
    void registerResponse(const QString& name, IResponseWare* response);
    bool containResponse(const QString& name);
    IResponseWare* convertableMatch(const QString&);

private:
    QMap<QString, IResponseWare*> m_responses;
    QMap<QString, IResponseWare*> m_convertableResponses;
};

$PackageWebCoreEnd
