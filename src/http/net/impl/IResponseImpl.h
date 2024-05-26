#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestRaw;

class IResponseImpl
{
public:
    IResponseImpl(IRequestRaw* raw);

public:
    QByteArray getContent();

private:
    QByteArray generateFirstLine();
    QByteArray generateHeadersContent(int contentSize); // 丑，但是好用啊
    void generateExternalHeadersContent(QByteArray& content);
    QString generateCookieHeaders();

public:
    IRequestRaw* raw{nullptr};
};

$PackageWebCoreEnd
