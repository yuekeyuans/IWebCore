#include "IXmlUtil.h"

$PackageWebCoreBegin

inline QDomNode IXmlUtil::toXml(const QString &content, bool& ok)
{
    QDomDocument doc;
    *ok = doc.setContent(content);
    return doc.documentElement();
}

inline QDomNode IXmlUtil::toXml(const QByteArray &content, bool& ok)
{
    QDomDocument doc;
    *ok = doc.setContent(content);
    return doc.documentElement();
}

$PackageWebCoreEnd
