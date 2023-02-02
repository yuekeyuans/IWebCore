#pragma once
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFileNode
{
public:
    IControllerFileNode() = default;
    bool isUrlExist(const QString& url) const;
    QString getFilePath(const QString& url) const ;

    void mountFilesToServer(const QString& dir, const QString& prefix="/");

private:
    QString getUnRegisteredFilePath(QString url) const;

private:
    mutable QHash<QString, QString> m_urlFileHash;
    QMap<QString, QString> m_urlPrefixMap;
};

$PackageWebCoreEnd
