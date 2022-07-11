#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFileNode
{
public:
    IControllerFileNode() = default;
    bool isUrlExist(const QString& url) const;
    QString getFilePath(const QString& url) const;

    void mountFilesToServer(const QString& path, const QString& prefix);

private:
    QVector<QPair<QString, QString>> m_nodes;
};

$PackageWebCoreEnd
