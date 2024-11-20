#include "IResponseImpl.h"
#include "core/util/IConstantUtil.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/net/IHeaderJar.h"
#include "http/response/IResponseManage.h"
#include "http/response/IResponseTemplateRenderer.h"
#include "http/response/IRendererResponse.h"

$PackageWebCoreBegin

inline static constexpr char NEW_LINE[] = "\r\n";

IResponseImpl::IResponseImpl(IRequestImpl& raw) : m_raw(raw)
{
}

std::vector<asio::const_buffer> IResponseImpl::getContent()
{
    // note: invalidFunction 在这个地方被调用
    // TODO: 这个不美观，之后考虑改进吧
//    if(raw.m_responseRaw->content.type == IResponseContent::Type::Invalid && raw.m_responseRaw->content.invalidFunction){
//        raw.m_responseRaw->content.invalidFunction(*raw.m_request);
//    }


    const auto& content = m_raw.m_respRaw.content.getContent();;

    m_content.emplace_back(generateFirstLine());
    if(content.size() != 0){
        m_content.emplace_back(generateHeadersContent(content.size()));
    }
    m_content.emplace_back(NEW_LINE);


//    if(!content.isEmpty() && raw.m_method != IHttpMethod::HEAD){       // 处理 head 方法
//        m_content.emplace_back(content);
//    }

    std::vector<asio::const_buffer> result;

    for(const auto& content : m_content){
        result.emplace_back(asio::buffer(content.data(), content.length()));
    }

    if(!content.empty()  && m_raw.m_reqRaw.m_method != IHttpMethod::HEAD){
        result.emplace_back(asio::buffer(content.data(), content.length()));
    }

    return result;
}

QByteArray IResponseImpl::generateFirstLine()
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionUtil::toString(m_raw.m_reqRaw.m_httpVersion)).append(" ")
        .append(IHttpStatusUtil::toString(m_raw.m_respRaw.status)).append(" ")
        .append(IHttpStatusUtil::toStringDescription(m_raw.m_respRaw.status)).append(NEW_LINE);

    return firstLine;
}

QByteArray IResponseImpl::generateHeadersContent(int contentSize)
{
    if(contentSize != 0){
        m_raw.m_headerJar->setResponseHeader(IHttpHeader::ContentLength, QString::number(contentSize));
        if(!m_raw.m_headerJar->containResponseHeaderKey(IHttpHeader::ContentType)
                && !m_raw.m_respRaw.mime.isEmpty()){
            m_raw.m_headerJar->setResponseHeader(IHttpHeader::ContentType, m_raw.m_respRaw.mime);
        }
    }

    QByteArray headersContent;
    auto keys = m_raw.m_respRaw.headers.uniqueKeys();
    for(const auto& key : keys){
        auto values = m_raw.m_respRaw.headers.values(key);
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
    const auto& cookies = m_raw.m_respRaw.cookies;
    for(auto cookie : cookies){
        auto val = cookie.toHeaderString();
        if(!val.isEmpty()){
            contents.push_back(val);
        }
    }
    return contents.join(NEW_LINE);
}

$PackageWebCoreEnd
