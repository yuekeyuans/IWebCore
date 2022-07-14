#pragma once
#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMime.h"
#include "web/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

struct IResponseWareRaw
{
public:
    void setMime(IHttpMime mime);
    void setMime(const QString& mime);

public:
    QString mimeString{"UNKNOWN"};   // when mime is unknown and mimeString is not empty ,mimeString take effect.

    IHttpStatus statusCode {IHttpStatus::OK_200};
    QMap<QString, QString> headers;
    QByteArray content{};
};

inline void IResponseWareRaw::setMime(IHttpMime mime){
    this->mimeString = IHttpMimeHelper::toString(mime);
}

inline void IResponseWareRaw::setMime(const QString &mime){
    this->mimeString = mime;
}

$PackageWebCoreEnd
