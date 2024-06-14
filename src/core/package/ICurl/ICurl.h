#pragma once

#include "core/base/IHeaderUtil.h"
#include "ICurlResponse.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin


class ICurl
{
    enum BodyType{
        FormData,
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
    ICurl& withFormFile(const QString& value);


    ICurl& withLimitRate(const QString&);

public:
    ICurlResponse exec();
    ICurlResponse execGet();
    ICurlResponse execPost();
    ICurlResponse execPut();
    ICurlResponse execDelete();

private:
    BodyType m_bodyType{None};
    QStringList m_pathArgs;
    QStringList m_headerArgs;
    QStringList m_bodyArgs;
    QStringList m_headers;
};

$PackageWebCoreEnd
