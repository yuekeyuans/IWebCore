#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class IHttpFolderMapping
{
public:
    IHttpFolderMapping() = default;

public:
    bool isEnabled() const;
    QString getFilePath(IStringView url) const;
    QStringList getFileEntries(const QString &url);
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QString getFolderDefaultFilePath(const QString&) const;

private:
    QMap<QString, QString> m_map;
    bool m_enabled{false};
    $QStringList defaultPages{"http.defaultPageNames"};
};

$PackageWebCoreEnd
