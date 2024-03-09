#pragma once
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IControllerFileNode
{
public:
    IControllerFileNode() = default;

public:
    bool isEnabled() const;
    QString getFilePath(const QString& url) const ;
    void mountMapping(const QString& dir, const QString& prefix="/");
    void travelPrint() const;

private:
    QMap<QString, QString> m_resourceMap;
    QHash<QString, QString> m_resourceFileMappings;
    bool m_resourceMappingEnabled{false};
};

$PackageWebCoreEnd
