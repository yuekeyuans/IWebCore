#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/jar/ICookieJar.h"
#include "http/response/IResponseContent.h"

$PackageWebCoreBegin

struct IResponseRaw
{
public:
    void setMime(IHttpMime mime);
    void setMime(const QString& mime);

    void setContent(QString&& content);
    void setContent(const QString& content);
    void setContent(QByteArray&& content);
    void setContent(const QByteArray& content);
    void setContent(const char* content);
    void setContent(const QFileInfo& content);
    void setContent(const QFile& file); // TODO: 这个不一定行， 得具体测试一下看看
    void setContent(IHttpInvalidUnit ware);
    void setFileContent(const QString& filePath);

public:
    bool isValid();

public:
    QString mime;
    IHttpStatusCode status {IHttpStatus::OK_200};
    QMultiHash<QString, QString> headers;
    std::list<ICookiePart> cookies;
    IResponseContent content;
};

$PackageWebCoreEnd
