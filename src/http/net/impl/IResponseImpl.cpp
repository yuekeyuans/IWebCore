#include "IResponseImpl.h"
#include "core/base/IConstantUtil.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/jar/IHeaderJar.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseTemplateRenderer.h"
#include "http/response/IRendererResponse.h"

$PackageWebCoreBegin

IResponseImpl::IResponseImpl(IReqRespRaw *raw)
    : raw(raw)
{
}

bool IResponseImpl::respond()
{
    const auto& content = raw->m_responseRaw->content.getAsBytes();
    raw->writeSocket(generateFirstLine());
    if(!content.isEmpty()){
        raw->writeSocket(generateHeadersContent(content.size()));
    }
    raw->writeSocket(IConstantUtil::NewLine);

    if(!content.isEmpty() && raw->m_method != IHttpMethod::HEAD){       // 处理 head 方法
        raw->writeSocket(content);
    }

    raw->flushSocket();
    return true;
}

QByteArray IResponseImpl::generateFirstLine()
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionUtil::toString(raw->m_httpVersion)).append(" ")
        .append(IHttpStatus::toString(raw->m_responseRaw->status)).append(" ")
        .append(IHttpStatus::toStringDescription(raw->m_responseRaw->status)).append(IConstantUtil::NewLine);

    return firstLine;
}

QByteArray IResponseImpl::generateHeadersContent(int contentSize)
{
    if(contentSize != 0){
        raw->m_headerJar->setResponseHeader(IHttpHeader::ContentLength, QString::number(contentSize));
        if(!raw->m_headerJar->containResponseHeaderKey(IHttpHeader::ContentType)
                && !raw->m_responseRaw->mime.isEmpty()){
            raw->m_headerJar->setResponseHeader(IHttpHeader::ContentType, raw->m_responseRaw->mime);
        }
    }

    QByteArray headersContent;
    for(const auto& key : raw->m_responseRaw->headers){
        auto values = raw->m_responseRaw->headers.values(key);
        headersContent.append(key).append(": ").append(values.join("; ")).append(IConstantUtil::NewLine);
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
    const auto& cookies = raw->m_responseRaw->cookies;
    for(auto cookie : cookies){
        auto val = cookie.toHeaderString();
        if(!val.isEmpty()){
            contents.push_back(val);
        }
    }
    return contents.join(IConstantUtil::NewLine);
}

$PackageWebCoreEnd
