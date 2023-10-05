#include "IXmlUtil.h"

$PackageWebCoreBegin

$InLine QDomNode IXmlUtil::toXml(const QString &content, bool *ok)
{
    QDomDocument doc;
    *ok = doc.setContent(content);
    return doc.documentElement();
}

$InLine QDomNode IXmlUtil::toXml(const QByteArray &content, bool *ok)
{
    QDomDocument doc;
    *ok = doc.setContent(content);
    return doc.documentElement();
}

$PackageWebCoreEnd
