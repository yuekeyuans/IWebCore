#pragma once
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFileNode
{
public:
    IControllerFileNode() = default;

public:
    bool isUrlExist(const QString& url) const;
    QString getFilePath(const QString& url) const ;
    void mountFilesToServer(const QString& dir, const QString& prefix="/");
    void travelPrint(int space=0) const;

private:
    QString getUnRegisteredFilePath(QString url) const;


private:
    mutable QHash<QString, QString> m_urlFileHash;
    QMap<QString, QString> m_urlPrefixMap;
};

$PackageWebCoreEnd
