#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/net/ICookieJar.h"
#include "http/response/IResponseContent.h"

$PackageWebCoreBegin

struct IResponseRaw
{
public:
    IResponseRaw() = default;
    void setMime(IHttpMime mime);
    void setMime(const QString& mime);

    void setContent(QString&& content);
    void setContent(const QString& content);
    void setContent(QByteArray&& content);
    void setContent(const QByteArray& content);
    void setContent(const char* content);
    void setContent(const QFileInfo& content);
    void setContent(IHttpInvalidWare ware);

public:
    bool isValid();

public:
    QString mime;
    IHttpStatus status {IHttpStatus::OK_200};
    QMultiHash<QString, QString> headers;
    std::list<ICookiePart> cookies;
    IResponseContent content;
};

$PackageWebCoreEnd
