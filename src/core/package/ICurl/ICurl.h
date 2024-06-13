#pragma once

#include "core/base/IHeaderUtil.h"
#include "ICurlResponse.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin


class ICurl
{
public:
    ICurl(const QString& url);

public:
    ICurl& b(const QString&);
    ICurl& withCookie(const QString&);

    ICurl& d(QString);
    ICurl& withPostData(const QString&);
    ICurl& withPostDataFile(const QString& path, IHttpMime);
    ICurl& withPostDataFile(const QString& path, const QString& ContentType);
    ICurl& dataUrlencode(const QString&);
    ICurl& withPostDataUrlEncode(const QString&);

    ICurl& F(const QString&);
    ICurl& withFormData(const QString& key, const QString& value);
    ICurl& withFormDataFile(const QString& key, const QString& path, const QString& fileName="", const QString& type="");

    ICurl& G();
    ICurl& withGenerateUrlQuery();

    ICurl& H(const QString&);
    ICurl& withHeader(const QString&);
    ICurl& withHeader(const QString&, const QString&);
    ICurl& withHeaderContentType(const QString&);

    ICurl& limitRate(const QString&);
    ICurl& withLimitRate(const QString&);

    ICurl& X(const QString&);
    ICurl& withMethod(const QString&);

public:
    ICurlResponse exec();
    ICurlResponse execGet();
    ICurlResponse execPost();
    ICurlResponse execPut();
    ICurlResponse execDelete();

private:
    QStringList m_args;
};

$PackageWebCoreEnd
