#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IXmlUtil
{
    QDomNode toXml(const QString& content, bool* ok);
    QDomNode toXml(const QByteArray& content, bool* ok);
};

$PackageWebCoreEnd
