#include "IResponseImpl.h"
#include "core/util/IConstantUtil.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/IHeaderJar.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseTemplateRenderer.h"
#include "http/response/IRendererResponse.h"

$PackageWebCoreBegin

inline static constexpr char NEW_LINE[] = "\r\n";

IResponseImpl::IResponseImpl(IRequestRaw *raw) : raw(raw)
{
}

std::vector<asio::const_buffer> IResponseImpl::getContent()
{
    // note: invalidFunction 在这个地方被调用
    // TODO: 这个不美观，之后考虑改进吧
//    if(raw->m_responseRaw->content.type == IResponseContent::Type::Invalid && raw->m_responseRaw->content.invalidFunction){
//        raw->m_responseRaw->content.invalidFunction(*raw->m_request);
//    }

    const auto& content = raw->m_responseRaw->content.getContent();

    m_content.emplace_back(generateFirstLine());
    if(content.size() != 0){
        m_content.emplace_back(generateHeadersContent(content.size()));
    }
    m_content.emplace_back(NEW_LINE);


//    if(!content.isEmpty() && raw->m_method != IHttpMethod::HEAD){       // 处理 head 方法
//        m_content.emplace_back(content);
//    }

    std::vector<asio::const_buffer> result;

    for(const auto& content : m_content){
        result.emplace_back(asio::buffer(content.data(), content.length()));
    }

    if(!content.empty()  && raw->m_method != IHttpMethod::HEAD){
        result.emplace_back(asio::buffer(content.data(), content.length()));
    }

    return result;
}

QByteArray IResponseImpl::generateFirstLine()
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionUtil::toString(raw->m_httpVersion)).append(" ")
        .append(IHttpStatusUtil::toString(raw->m_responseRaw->status)).append(" ")
        .append(IHttpStatusUtil::toStringDescription(raw->m_responseRaw->status)).append(NEW_LINE);

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
    auto keys = raw->m_responseRaw->headers.uniqueKeys();
    for(const auto& key : keys){
        auto values = raw->m_responseRaw->headers.values(key);
        headersContent.append(key).append(":").append(values.join(";")).append(NEW_LINE);
    }

    generateExternalHeadersContent(headersContent);
    return headersContent;
}

void IResponseImpl::generateExternalHeadersContent(QByteArray& content)
{
    content.append("Server: IWebCore").append(NEW_LINE);

    auto cookieContent = generateCookieHeaders();
    if(!cookieContent.isEmpty()){
        content.append(cookieContent).append(NEW_LINE);
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
    return contents.join(NEW_LINE);
}

$PackageWebCoreEnd
