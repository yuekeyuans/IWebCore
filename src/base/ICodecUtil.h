#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ICodecUtil
{
    QByteArray toBase64(const QString& content);
    QByteArray toBase64(const QByteArray& content);
    QByteArray toBase64(const char* content);

    QByteArray fromBase64(const QString& content);
    QByteArray fromBase64(const QByteArray& content);
    QByteArray fromBase64(const char* content);

    QByteArray urlEncode(const QString& rawUrl);
    QByteArray urlEncode(const QByteArray& rawUrl);

    QByteArray urlDecode(const QString& rawUrl);
    QByteArray urlDecode(const QByteArray& rawUrl);

    QString pathEncode(const QString& rawPath);
};

$PackageWebCoreEnd
