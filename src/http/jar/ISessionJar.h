#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/jar/IJarUnit.h"

$PackageWebCoreBegin

class ISessionWare;
class ISessionJar : public IJarUnit, IRegisterMetaTypeUnit<ISessionJar>
{
public:
    ISessionJar();
    ISessionJar(IReqRespRaw* m_raw);

public:
    bool isValid() const override;
    QVariant value(const QString key);
    void setValue(const QString key, QVariant);

private:
    ISessionWare* m_sessionWare{};
    QString m_sessionId{};
};

$PackageWebCoreEnd
