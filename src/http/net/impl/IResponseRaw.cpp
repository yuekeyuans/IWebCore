#include "IResponseRaw.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "Http/net/impl/IRequestImpl.h"

#include "http/response/content/IQStringResponseContent.h"
#include "http/response/content/IQByteArrayResposneContent.h"

$PackageWebCoreBegin

inline static constexpr char NEW_LINE[] = "\r\n";

void IResponseRaw::setMime(IHttpMime mime)
{
    this->m_mime = IHttpMimeUtil::toString(mime);
}

void IResponseRaw::setMime(const QString &mime)
{
    this->m_mime = mime;
}

void IResponseRaw::setContent(QString &&value)
{
    m_contents.push_back(new IQStringResponseContent(std::move(value)));
}

void IResponseRaw::setContent(const QString &value)
{
    m_contents.push_back(new IQStringResponseContent(value));
}

void IResponseRaw::setContent(QByteArray &&value)
{
    m_contents.push_back(new IQByteArrayResposneContent(std::move(value)));
}

void IResponseRaw::setContent(const QByteArray &value)
{
    m_contents.push_back(new IQByteArrayResposneContent(value));
}

void IResponseRaw::setContent(const char *value)
{
    m_contents.push_back(new IQByteArrayResposneContent(value));
}

void IResponseRaw::setContent(const QFileInfo &value)
{
//    m_responseContent.setFileContent(value.absoluteFilePath());
}

void IResponseRaw::setContent(IHttpInvalidWare ware)
{
//    m_responseContent.setContent(std::move(ware));
}

std::vector<asio::const_buffer> IResponseRaw::getContent(IRequestImpl& impl)
{
    std::vector<asio::const_buffer> result;
    m_store.emplace_back(generateFirstLine(impl));

    IStringView content{};
    if(!m_contents.empty()){
        content = m_contents.back()->getContent();
    }
    if(content.size() != 0){
        m_store.emplace_back(generateHeadersContent(impl, content.size()));
    }
    m_store.emplace_back(NEW_LINE);

    for(const auto& val : m_store){
        result.emplace_back(asio::buffer(val.data(), val.length()));
    }

    if(!content.empty()  && impl.m_reqRaw.m_method != IHttpMethod::HEAD){
        result.emplace_back(asio::buffer(content.data(), content.length()));
    }

    return result;
}

QByteArray IResponseRaw::generateFirstLine(IRequestImpl& impl)
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionUtil::toString(impl.m_reqRaw.m_httpVersion)).append(" ")
            .append(IHttpStatusUtil::toString(impl.m_respRaw.m_status)).append(" ")
            .append(IHttpStatusUtil::toStringDescription(impl.m_respRaw.m_status)).append(NEW_LINE);

    return firstLine;
}

QByteArray IResponseRaw::generateHeadersContent(IRequestImpl& m_raw, int contentSize)
{
    if(contentSize != 0){
        m_raw.m_headerJar.setResponseHeader(IHttpHeader::ContentLength, QString::number(contentSize));
        if(!m_raw.m_headerJar.containResponseHeaderKey(IHttpHeader::ContentType)
                && !m_raw.m_respRaw.m_mime.isEmpty()){
            m_raw.m_headerJar.setResponseHeader(IHttpHeader::ContentType, m_raw.m_respRaw.m_mime);
        }
    }

    QByteArray headersContent;
    auto keys = m_raw.m_respRaw.m_headers.uniqueKeys();
    for(const auto& key : keys){
        auto values = m_raw.m_respRaw.m_headers.values(key);
        headersContent.append(key).append(":").append(values.join(";")).append(NEW_LINE);
    }

    generateExternalHeadersContent(headersContent);
    return headersContent;
}

void IResponseRaw::generateExternalHeadersContent(QByteArray &content)
{
    content.append("Server: IWebCore").append(NEW_LINE);

    auto cookieContent = generateCookieHeaders();
    if(!cookieContent.isEmpty()){
        content.append(cookieContent).append(NEW_LINE);
    }
}

QString IResponseRaw::generateCookieHeaders()
{
    QStringList contents;
    for(const auto& cookie : m_cookies){
        auto val = cookie.toHeaderString();
        if(!val.isEmpty()){
            contents.push_back(val);
        }
    }
    return contents.join(NEW_LINE);
}

$PackageWebCoreEnd
