#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IXmlUtil
{
    QDomNode toXml(const QString& content, bool& ok);
    QDomNode toXml(const QByteArray& content, bool& ok);
}

$PackageWebCoreEnd

#include "IXmlUtil.cpp"
