#pragma once
#include "core/base/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/response/IResponseContent.h"

$PackageWebCoreBegin

struct IResponseWareRaw
{
public:
    void setMime(IHttpMime mime);
    void setMime(const QString& mime);

    // TODO: 添加 setContent;
    void setContent(QString&& content);
    void setContent(const QString& content);

    void setContent(QByteArray&& content);
    void setContent(const QByteArray& content);
    void setContent(const char* content);

    void setContent(const QFileInfo& content);
    void setContent(const QFile& file); // TODO: 这个不一定行， 得具体测试一下看看
    void setFileContent(const QString& filePath);

    void setInvalid(IHttpStatus status, QString reason);

public:
    QString mimeString {"UNKNOWN"};   // when mime is unknown and mimeString is not empty ,mimeString take effect.
    IHttpStatus statusCode {IHttpStatus::UNKNOWN};
    QMap<QString, QString> headers;
    IResponseContent content;
};

$PackageWebCoreEnd
