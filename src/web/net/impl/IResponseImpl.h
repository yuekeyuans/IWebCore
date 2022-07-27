#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IResponseImpl
{
public:
    IResponseImpl(IReqRespRaw* raw);

    bool respond();

    QByteArray generateFirstLine();

    QByteArray generateHeadersContent(int contentSize); // 丑，但是好用啊
    void generateExternalHeadersContent(QByteArray& content);
    QString generateCookieHeaders();

public:
    IReqRespRaw* raw{nullptr};
    bool m_responded{false};
};

$PackageWebCoreEnd
