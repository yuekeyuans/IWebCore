#pragma once
#include <QtCore>
#include "biscuits/IHttpMime.h"
#include "biscuits/IHttpStatus.h"

$PackageWebCoreBegin

struct IResponseWareRaw
{
    /// the mime of unknown means this value (or return value) must be reinitialized,
    /// otherwise the error will occurred
    IHttpMime mime{IHttpMime::UNKNOWN};
    IHttpStatus statusCode {IHttpStatus::OK_200};
    QMap<QString, QString> headers;
    QByteArray content{};
};

$PackageWebCoreEnd
