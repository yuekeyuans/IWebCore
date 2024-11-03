#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class IHttpResourceMapping
{
public:
    IHttpResourceMapping() = default;

public:
    bool isEnabled() const;
    QString getFilePath(IStringView url) const ;
    QStringList getFileEntries(const QString& url);
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QMap<QString, QString> m_map;
    QMap<QString, QString> m_fileMappings;
    bool m_enabled{false};
};

$PackageWebCoreEnd
