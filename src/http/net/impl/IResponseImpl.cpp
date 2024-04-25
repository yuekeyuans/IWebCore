#include "IResponseImpl.h"
#include "core/base/IConstantUtil.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/jar/IHeaderJar.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseTemplateRenderer.h"
#include "http/response/IRendererResponse.h"

$PackageWebCoreBegin

IResponseImpl::IResponseImpl(IReqRespRaw *raw)
{
    this->raw = raw;
}

bool IResponseImpl::respond()
{
    if(!raw->valid()){
        auto path = IResponseManage::instance()->getTemplateRenderer()->getPage(raw->m_responseStatus);
        if(!path.isEmpty()){
            QJsonObject obj;
            obj["status_code"] = IHttpStatus::toString(raw->m_responseStatus);
            obj["error_info"] = raw->m_responseContent.contentString;

            IRendererResponse response(path, obj);
            raw->m_responseMime = IHttpMimeUtil::toString(IHttpMime::TEXT_HTML_UTF8);
            raw->m_responseContent.setContent(response.getContent().contentString);
        }
    }

    const auto& content = raw->m_responseContent.getAsBytes();

    raw->writeSocket(generateFirstLine());
    raw->writeSocket(generateHeadersContent(content.size()));
    raw->writeSocket(IConstantUtil::NewLine);

    if(content.length() != 0 && raw->m_method != IHttpMethod::HEAD){       // 处理 head 方法
        raw->writeSocket(content);
    }

    raw->flushSocket();
    return true;
}

QByteArray IResponseImpl::generateFirstLine()
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionUtil::toString(raw->m_httpVersion)).append(" ")
        .append(IHttpStatus::toString(raw->m_responseStatus)).append(" ")
        .append(IHttpStatus::toStringDescription(raw->m_responseStatus)).append(IConstantUtil::NewLine);

    return firstLine;
}

QByteArray IResponseImpl::generateHeadersContent(int contentSize)
{
    if(contentSize != 0){
        raw->m_headerJar->setResponseHeader(IHttpHeader::ContentLength, QString::number(contentSize));
        if(!raw->m_headerJar->containResponseHeaderKey(IHttpHeader::ContentType)){
            raw->m_headerJar->setResponseHeader(IHttpHeader::ContentType, raw->m_responseMime);
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
