#pragma once

#include "ICurlResponse.h"

// NOTE: this file is only for test request.
class ICurl
{
public:
    ICurl(QString url);

public:
    ICurl& b(QString);
    ICurl& withCookie(QString);

    ICurl& d(QString);
    ICurl& withPostData(QString);
    ICurl& withPostDataFile(QString path);
    ICurl& dataUrlencode(QString);
    ICurl& withPostDataUrlEncode(QString);

    ICurl& F(QString);
    ICurl& withFormData(QString key, QString value);
    ICurl& withFormDataFile(QString key, QString path, QString fileName="", QString type="");

    ICurl& G();
    ICurl& withGenerateUrlQuery();

    ICurl& H(QString);
    ICurl& withHeader(QString);
    ICurl& withHeader(QString, QString);
    ICurl& withHeaderContentType(QString);

    ICurl& limitRate(QString);
    ICurl& withLimitRate(QString);

    ICurl& X(QString);
    ICurl& withMethod(QString);

public:
    ICurlResponse exec();
    ICurlResponse execGet();
    ICurlResponse execPost();
    ICurlResponse execPut();
    ICurlResponse execDelete();

private:
    QStringList m_args;
};

