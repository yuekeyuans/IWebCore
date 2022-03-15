#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IResponseImpl
{
public:
    IResponseImpl(IReqRespRaw* raw);

    bool respond();

    void write(const QByteArray& content);
    void flush();
    QByteArray generateFirstLine();

    QByteArray generateHeadersContent();
    void generateExternalHeadersContent(QByteArray& content);
    QString generateCookieHeaders();

public:
    IReqRespRaw* raw{nullptr};
};

$PackageWebCoreEnd
