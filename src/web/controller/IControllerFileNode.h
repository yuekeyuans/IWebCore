#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFileNode
{
public:
    IControllerFileNode() = default;
    bool isUrlExist(const QString& url) const;
    QString getFilePath(const QString& url) const;

    void mountFilesToServer(const QString& path, const QString& prefix="/");

private:
    QHash<QString, QString> m_urlFileHash;
};

$PackageWebCoreEnd
