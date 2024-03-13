#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerDirectoryNode
{
public:
    IControllerDirectoryNode() = default;

public:
    bool isEnabled() const;
    QString getFilePath(const QString& url) const;
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QMap<QString, QString> m_map;
    bool m_enabled{false};
};

$PackageWebCoreEnd
