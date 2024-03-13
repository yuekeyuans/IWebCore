#pragma once
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerResourceMapping
{
public:
    IControllerResourceMapping() = default;

public:
    bool isEnabled() const;
    QString getFilePath(const QString& url) const ;
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QMap<QString, QString> m_map;
    QHash<QString, QString> m_fileMappings;
    bool m_enabled{false};
};

$PackageWebCoreEnd
