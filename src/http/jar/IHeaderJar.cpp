#include "IHeaderJar.h"

#include "core/base/IToeUtil.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IHeaderJar::IHeaderJar() : IJarUnit(nullptr)
{
    $Ast->fatal("IHeaderJar_CREATE_ERROR");
}

const QList<QPair<QString, QString>>& IHeaderJar::requestHeaders() const
{
    return m_raw->m_requestHeaders;
}

QList<QPair<QString, QString> > &IHeaderJar::requestHeaders()
{
    return m_raw->m_requestHeaders;
}

QStringList IHeaderJar::requestHeaderKeys() const
{
    QStringList ret;
    for(const auto& pair : m_raw->m_requestHeaders){
        if(!ret.contains(pair.first)){
            ret.append(pair.first);
        }
    }
    return ret;
}

bool IHeaderJar::containRequestHeaderKey(const QString &key) const
{
    for(const auto& pair : m_raw->m_requestHeaders){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

QString IHeaderJar::getRequestHeaderValue(const QString &key, bool& ok) const
{
    for(const auto& pair : m_raw->m_requestHeaders){
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
    for(const auto& pair : m_raw->m_requestHeaders){
        if(pair.first == key){
            ret.append(pair.second);
        }
    }
    return ret;
}

const QList<QPair<QString, QString> > &IHeaderJar::responseHeaders() const
{
    return m_raw->m_responseHeaders;
}

QList<QPair<QString, QString> > &IHeaderJar::responseHeaders()
{
    return m_raw->m_responseHeaders;
}

QStringList IHeaderJar::responseHeaderKeys() const
{
    QStringList ret;
    for(const auto& pair : m_raw->m_responseHeaders){
        if(!ret.contains(pair.first)){
            ret.append(pair.first);
        }
    }
    return ret;
}

bool IHeaderJar::containResponseHeaderKey(const QString &key) const
{
    for(const auto& pair : m_raw->m_responseHeaders){
        if(pair.first == key){
            return true;
        }
    }
    return false;
}

QString IHeaderJar::getResponseHeaderValue(const QString &key, bool& ok) const
{
    for(const auto& pair : m_raw->m_requestHeaders){
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
    for(const auto& pair : m_raw->m_responseHeaders){
        if(pair.first == key){
            ret.append(pair.second);
        }
    }
    return ret;
}

// NOTE: 注意这两者之间的差别， setReponseHeader是，如果有这个值，就替换， addResponseHeader 表示不管怎样，直接添加。
void IHeaderJar::addResponseHeader(const QString &key, const QString &value)
{
    return m_raw->m_responseHeaders.append({key, value});
}

void IHeaderJar::setResponseHeader(const QString &key, const QString &value)
{
    auto it=m_raw->m_responseHeaders.begin();
    for(; it!=m_raw->m_responseHeaders.end(); it++){
        if(it->first == key){
            it->second = value;
            return;
        }
    }

    addResponseHeader(key, value);
}

void IHeaderJar::deleteReponseHeader(const QString &key)
{
    auto& header = m_raw->m_responseHeaders;
    for(auto it=header.begin(); it!= header.end();){
        if(it->first == key){
            it = header.erase(it);
        }else{
            it++;
        }
    }
}

$PackageWebCoreEnd
