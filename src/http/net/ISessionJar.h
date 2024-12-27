#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/net/IJarUnit.h"

$PackageWebCoreBegin

class ISessionWare;
class ISessionJar : public IJarUnit
{
public:
    ISessionJar(IRequestImpl& m_impl);

public:
    bool isValid() const;
    QVariant value(const QString key);
    void setValue(const QString key, QVariant);

private:
    ISessionWare* m_sessionWare{};
    QString m_sessionId{};
};

$PackageWebCoreEnd
