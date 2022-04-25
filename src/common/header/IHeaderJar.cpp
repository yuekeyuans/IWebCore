#include "IHeaderJar.h"

#include "base/IToeUtil.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

QStringList IHeaderJar::requestHeaderKeys()
{
    QStringList ret;
    for(const auto& pair : raw->m_requestHeaders){
        if(ret.indexOf(pair.first)<0){
            ret.append(pair.first);
        }
    }
    return ret;
}

QString IHeaderJar::getRequestHeaderValue(const QString &key, bool *ok) const
{
    for(const auto& pair : raw->m_requestHeaders){
        if(pair.first == key){
            IToeUtil::setOk(ok, true);
            return pair.second;
        }
    }
    IToeUtil::setOk(ok, false);
    return "";
}

const QList<QPair<QString, QByteArray>>& IHeaderJar::requestHeaders() const
{
    return raw->m_requestHeaders;
}

bool IHeaderJar::isValid() const
{
    return raw != nullptr;
}

$PackageWebCoreEnd
