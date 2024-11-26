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
    void registerResponse(const std::string& name, IResponseWare* response);
    bool containResponse(const std::string& name);
    IResponseWare* convertableMatch(const std::string&);

private:
    QMap<std::string, IResponseWare*> m_responses;
    QMap<std::string, IResponseWare*> m_convertableResponses;
};

$PackageWebCoreEnd
