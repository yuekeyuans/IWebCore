#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IResponseImpl
{
public:
    IResponseImpl(IReqRespRaw* raw);
    bool respond();

private:
    QByteArray generateFirstLine();
    QByteArray generateHeadersContent(int contentSize); // 丑，但是好用啊
    void generateExternalHeadersContent(QByteArray& content);
    QString generateCookieHeaders();

public:
    IReqRespRaw* raw{nullptr};
};

$PackageWebCoreEnd
