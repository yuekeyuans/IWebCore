#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"


$PackageWebCoreBegin

class IHttpParameterRestrictInterface;
class IHttpParameterRestrictManage : public ISingletonUnit<IHttpParameterRestrictManage>
{
public:
    IHttpParameterRestrictManage() = default;

public:
    void addRestrict(IHttpParameterRestrictInterface*);
    QStringList getRestrictNames() const;
    IHttpParameterRestrictInterface* getRestrict(const QString& name);

private:
    QMap<QString, IHttpParameterRestrictInterface*> m_map;
};

$PackageWebCoreEnd
