#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class ICurlResponse
{
public:
    ICurlResponse(QByteArray data);

private:
    void parse();
    void parseHead(QByteArray);
    void parseFirstLine(QString);

public:
    bool m_error{false};
    int m_status;
    QByteArray m_content;
    QByteArray m_body;
    QMap<QString, QString> m_headers;
};

$PackageWebCoreEnd
