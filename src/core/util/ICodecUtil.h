#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ICodecUtil
{
    QByteArray urlEncode(const QString& rawUrl);
    QByteArray urlEncode(const QByteArray& rawUrl);

    QByteArray urlDecode(const QString& rawUrl);
    QByteArray urlDecode(const QByteArray& rawUrl);

    QString pathEncode(const QString& rawPath);
}

$PackageWebCoreEnd

#include "ICodecUtil.cpp"
