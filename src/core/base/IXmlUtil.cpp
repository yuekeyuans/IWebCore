#include "IXmlUtil.h"

$PackageWebCoreBegin

QDomNode IXmlUtil::toXml(const QString &content, bool *ok)
{
    QDomDocument doc;
    *ok = doc.setContent(content);
    return doc.documentElement();
}

QDomNode IXmlUtil::toXml(const QByteArray &content, bool *ok)
{
    QDomDocument doc;
    *ok = doc.setContent(content);
    return doc.documentElement();
}


$PackageWebCoreEnd
