#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace ICodecUtil
{
    QByteArray toBase64(const QString& content);
    QByteArray toBase64(const QByteArray& content);
    QByteArray toBase64(const char* content);

    QByteArray fromBase64(const QString& content);
    QByteArray fromBase64(const QByteArray& content);
    QByteArray fromBase64(const char* content);

    quint16 crc16(const QString& content);

    QByteArray compress(const QString& content, int level=-1);
    QByteArray compress(const QByteArray& content, int level=-1);
    QByteArray compress(const char* content, int level=-1);

    QByteArray uncompress(const QString& content);
    QByteArray uncompress(const QByteArray& content);
    QByteArray uncompress(const char* content);

    QByteArray urlEncode(const QString& rawUrl);
    QByteArray urlEncode(const QByteArray& rawUrl);

    QByteArray urlDecode(const QString& rawUrl);
    QByteArray urlDecode(const QByteArray& rawUrl);

    QString pathEncode(const QString& rawPath);
};

$PackageWebCoreEnd
