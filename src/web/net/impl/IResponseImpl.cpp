#include "IResponseImpl.h"
#include "base/IConstantUtil.h"
#include "web/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

IResponseImpl::IResponseImpl(IReqRespRaw *raw)
{
    this->raw = raw;
}

bool IResponseImpl::respond()
{
    write(generateFirstLine());
    write(generateHeadersContent());
    write(IConstantUtil::NewLine);

    if(raw->m_responseContent.length() != 0 && raw->m_method != IHttpMethod::HEAD){       // 处理 head 方法
        write(raw->m_responseContent);
    }

    flush();
    return true;
}

void IResponseImpl::write(const QByteArray &content)
{
    if(!content.isEmpty()){
        raw->m_socket->write(content);
    }
}

void IResponseImpl::flush()
{
    raw->m_socket->flush();
}

QByteArray IResponseImpl::generateFirstLine()
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionHelper::toString(raw->m_httpVersion)).append(" ")
        .append(IHttpStatusHelper::toString(raw->m_responseStatus)).append(" ")
        .append(IHttpStatusHelper::toStringDescription(raw->m_responseStatus)).append(IConstantUtil::NewLine);

    return firstLine;
}

QByteArray IResponseImpl::generateHeadersContent()
{
    auto len = raw->m_responseContent.length();
    if(len != 0){
        raw->m_headerJar.setResponseHeader(IHttpHeader::ContentLength, QString::number(len));
        if(!raw->m_headerJar.containResponseHeaderKey(IHttpHeader::ContentType)){
            raw->m_headerJar.setResponseHeader(IHttpHeader::ContentType, raw->m_responseMime);
        }
    }

    QByteArray headersContent;
    for(const auto& pair : raw->m_responseHeaders){
        headersContent.append(pair.first).append(": ").append(pair.second).append(IConstantUtil::NewLine);
    }

    generateExternalHeadersContent(headersContent);
    return headersContent;
}

void IResponseImpl::generateExternalHeadersContent(QByteArray& content)
{
    if(IConstantUtil::IServerNameMiddleWareEnabeld){
        content.append("Server: ").append(IConstantUtil::ServerName).append(IConstantUtil::NewLine);
    }

    if(IConstantUtil::ICookiePluginEnabled){
        auto cookieContent = generateCookieHeaders();
        if(!cookieContent.isEmpty()){
            content.append(cookieContent).append(IConstantUtil::NewLine);
        }
    }
}

QString IResponseImpl::generateCookieHeaders()
{
    QStringList contents;
    const auto& cookies = raw->m_responseCookies;
    for(auto cookie : cookies){
        auto val = cookie.toHeaderString();
        if(!val.isEmpty()){
            contents.push_back(val);
        }
    }
    return contents.join(IConstantUtil::NewLine);
}

$PackageWebCoreEnd
