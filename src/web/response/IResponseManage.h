#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

struct INody;
class IResponseWare;

class IResponseManage : public ISingletonUnit<IResponseManage>
{
public:
    IResponseManage() = default;

public:
    void registerResponseType(IResponseWare* response);
    IResponseWare* convertMatch(const QString&);

    void registerNodyProcesser(const QString& path, INody*);
    INody* getNodyProcessor(const QString& path);
    bool isNodyPathExist(const QString& path);

private:
    QVector<IResponseWare*> m_responses;
    QMap<QString, IResponseWare*> m_convertResponses;
    QHash<QString, INody*> m_nodyProcessor;
};

$PackageWebCoreEnd
