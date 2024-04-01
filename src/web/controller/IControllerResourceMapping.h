#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class IControllerResourceMapping
{
public:
    IControllerResourceMapping() = default;

public:
    bool isEnabled() const;
    QString getFilePath(const QString& url) const ;
    QStringList getFileEntries(const QString& url);
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QMap<QString, QString> m_map;
    QMap<QString, QString> m_fileMappings;
    bool m_enabled{false};
};

$PackageWebCoreEnd
