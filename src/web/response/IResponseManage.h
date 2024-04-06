#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

struct INody;
class IResponseWare;
class IResponseTemplateInterface;
class IResponseManage : public ISingletonUnit<IResponseManage>
{
public:
    IResponseManage() = default;
    ~IResponseManage();

public:
    void registerResponseType(IResponseWare* response);
    IResponseWare* convertMatch(const QString&);


    IResponseTemplateInterface* getRenderTemplate();
    void setRenderTemplate(IResponseTemplateInterface*);
//    void registerNodyProcesser(const QString& path, INody*);
//    INody* getNodyProcessor(const QString& path);
//    bool isNodyPathExist(const QString& path);

private:
    QVector<IResponseWare*> m_responses;
    QMap<QString, IResponseWare*> m_convertResponses;
    QHash<QString, INody*> m_nodyProcessor;
    IResponseTemplateInterface* m_renderTemplate{};
};

$PackageWebCoreEnd
