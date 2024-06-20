#pragma once

#include "core/base/IHeaderUtil.h"
#include "ICurlResponse.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin


class ICurl
{
    enum BodyType{
        UrlEncoded,
        MultiPart,
        File,
        Json,
        Raw,
        None
    };

public:
    ICurl(const QString& url);

public:

    ICurl& withPathArg(const QString& data);
    ICurl& withPathArg(const QString& name, const QString& value);
    ICurl& withPathArgs(QMap<QString, QString> args);

    ICurl& withHeader(const QString&);
    ICurl& withHeader(const QString&, const QString&);
    ICurl& withContentType(IHttpMime);
    ICurl& withContentType(const QString& contentType);

    ICurl& withJsonBody(const QString& value);
    ICurl& withFormData(const QString& value);
    ICurl& withFormData(const QString& key, const QString& value);
    ICurl& withFormFile(const QString& name, const QString& path, const QString& fileName="", const QString& mime="");

    ICurl& withEncodeData(const QString& value);
    ICurl& withEncodeBinary(const QString& path);

    ICurl& withBinary(const QString& path, QString mime);
    ICurl& withBinary(const QString& path, IHttpMime type=IHttpMime::APPLICATION_OCTET_STREAM);

    ICurl& withRawData();

    ICurl& withLimitRate(const QString&);

public:
    ICurlResponse exec();
    ICurlResponse execGet();
    ICurlResponse execPost();
    ICurlResponse execPut();
    ICurlResponse execDelete();

private:
    BodyType m_bodyType{None};
    QString m_contentType;
    QStringList m_cmds;
};

$PackageWebCoreEnd
