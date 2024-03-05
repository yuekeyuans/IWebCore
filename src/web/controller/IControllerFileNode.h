#pragma once
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFileNode
{
public:
    IControllerFileNode() = default;

public:
    QString getFilePath(const QString& url) const ;
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint(int space=0) const;

private:
    QMap<QString, QString> m_resourceMap;
    QHash<QString, QString> m_resourceFileMappings;
    bool m_resourceMappingEnabled{false};
};

$PackageWebCoreEnd
