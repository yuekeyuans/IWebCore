#include "IHeaderJar.h"

#include "base/IToeUtil.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

QStringList IHeaderJar::requestHeaderKeys()
{
    return raw->m_requestHeaders.keys();
}

QString IHeaderJar::getRequestHeaderValue(const QString &key, bool *ok) const
{
    if(raw->m_requestHeaders.contains(key)){
        IToeUtil::setOk(ok, true);
        return raw->m_requestHeaders[key];
    }
    IToeUtil::setOk(ok, false);
    return "";
}

const QMap<QString, QByteArray> IHeaderJar::requestHeaders() const
{
    return raw->m_requestHeaders;
}

bool IHeaderJar::isValid() const
{
    return raw != nullptr;
}

$PackageWebCoreEnd
