﻿#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFolderMapping
{
public:
    IControllerFolderMapping() = default;

public:
    bool isEnabled() const;
    QString getFilePath(const QString& url) const;
    QStringList getFileEntries(const QString &url);
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QString getFolderDefaultFilePath(const QString&) const;

private:
    QMap<QString, QString> m_map;
    bool m_enabled{false};
};

$PackageWebCoreEnd