#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequestImpl;
class IResponseImpl
{
public:
    IResponseImpl(IRequestImpl& m_raw);

public:
    std::vector<asio::const_buffer> getContent();

private:
    QByteArray generateFirstLine();
    QByteArray generateHeadersContent(int contentSize); // 丑，但是好用啊
    void generateExternalHeadersContent(QByteArray& content);
    QString generateCookieHeaders();

public:
    IRequestImpl& m_raw;
    std::vector<QByteArray> m_content;
};

$PackageWebCoreEnd
