﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/net/IJarUnit.h"

$PackageWebCoreBegin

class ISessionWare;
class ISessionJar : public IJarUnit, IRegisterMetaTypeUnit<ISessionJar>
{
public:
    ISessionJar();
    ISessionJar(IRequestRaw* m_raw);

public:
    bool isValid() const override;
    QVariant value(const QString key);
    void setValue(const QString key, QVariant);

private:
    ISessionWare* m_sessionWare{};
    QString m_sessionId{};
};

$PackageWebCoreEnd
