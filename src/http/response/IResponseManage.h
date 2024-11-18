#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

struct INody;
class IResponseWare;
class IResponseTemplateRenderer;
class IResponseManage : public ISingletonUnit<IResponseManage>
{
public:
    IResponseManage() = default;
    ~IResponseManage();

public:
    void registerResponseType(const QString& name, IResponseWare* response);
    bool containResponseType(const QString& name);

    IResponseWare* convertMatch(const QString&);

    IResponseTemplateRenderer* getTemplateRenderer();
    void setTemplateRenderer(IResponseTemplateRenderer*);

private:
    QMap<QString, IResponseWare*> m_responses;
    QMap<QString, IResponseWare*> m_convertResponses;
    QHash<QString, INody*> m_nodyProcessor;
    IResponseTemplateRenderer* m_templateRenderer{};
};

$PackageWebCoreEnd
