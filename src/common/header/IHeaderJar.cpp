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

QStringList IHeaderJar::getRequestHeaderValues(const QString &key) const
{
    QStringList ret;
    for(const auto& pair : raw->m_requestHeaders){
        if(pair.first == key){
            ret.append(pair.second);
        }
    }
    return ret;
}

bool IHeaderJar::containRequestHeaderKey(const QString &key)
{
    for(const auto& pair : raw->m_requestHeaders){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

const QList<QPair<QString, QByteArray>>& IHeaderJar::requestHeaders() const
{
    return raw->m_requestHeaders;
}

bool IHeaderJar::containResponseHeaderKey(const QString &key)
{
    for(const auto& pair : raw->m_responseHeaders){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

QString IHeaderJar::getResponseHeaderValue(const QString &key, bool* ok) const
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

QStringList IHeaderJar::getResponseHeaderValues(const QString &key) const
{
    QStringList ret;
    for(const auto& pair : raw->m_responseHeaders){
        if(pair.first == key){
            ret.append(pair.second);
        }
    }
    return ret;
}

void IHeaderJar::addResponseHeader(const QString &key, const QString &value)
{
    return raw->m_responseHeaders.append({key, value.toUtf8()});
}

bool IHeaderJar::isValid() const
{
    return raw != nullptr;
}

$PackageWebCoreEnd
