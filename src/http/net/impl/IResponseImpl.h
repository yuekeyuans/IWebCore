#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestRaw;

class IResponseImpl
{
public:
    IResponseImpl(IRequestRaw* raw);

public:
    std::vector<asio::const_buffer> getContent();

private:
    QByteArray generateFirstLine();
    QByteArray generateHeadersContent(int contentSize); // 丑，但是好用啊
    void generateExternalHeadersContent(QByteArray& content);
    QString generateCookieHeaders();

public:
    IRequestRaw* raw{nullptr};
    std::vector<QByteArray> m_content;
};

$PackageWebCoreEnd
