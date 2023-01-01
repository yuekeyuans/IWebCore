#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/jar/IJarUnit.h"

$PackageWebCoreBegin

// TODO: Session 在框架当中应该如何支持？ SessionJar 又是个啥？

class ISessionJar : public IJarUnit, IRegisterMetaTypeUnit<ISessionJar>
{
    Q_GADGET
    $UseMetaRegistration(ISessionJar)
public:
    using IJarUnit::IJarUnit;

public:
    ISessionJar();

    QVariant value(const QString key);
    void setValue(const QString key, QVariant);

private:
    QString m_sessionId;
};

$PackageWebCoreEnd
