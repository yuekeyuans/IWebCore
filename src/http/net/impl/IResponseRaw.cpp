#include "IResponseRaw.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "Http/net/impl/IRequestImpl.h"

#include "http/response/content/IQStringResponseContent.h"
#include "http/response/content/IQByteArrayResponseContent.h"
#include "http/response/content/IInvalidReponseContent.h"
#include "http/response/content/IFileResponseContent.h"
#include "http/response/content/IStdStringResponseContent.h"

$PackageWebCoreBegin

inline static constexpr char NEW_LINE[] = "\r\n";


namespace detail
{

QByteArray generateFirstLine(IRequestImpl& impl)
{
    QByteArray firstLine;
    firstLine.append(IHttpVersionUtil::toString(impl.m_reqRaw.m_httpVersion)).append(" ")
            .append(IHttpStatusUtil::toString(impl.m_respRaw.m_status)).append(" ")
            .append(IHttpStatusUtil::toStringDescription(impl.m_respRaw.m_status)).append(NEW_LINE);

    return firstLine;
}

QString generateCookieHeaders(IResponseRaw& raw)
{
    QStringList contents;
    for(const auto& cookie : raw.m_cookies){
        auto val = cookie.toHeaderString();
        if(!val.isEmpty()){
            contents.push_back(val);
        }
    }
    return contents.join(NEW_LINE);
}

void generateExternalHeadersContent(IResponseRaw& raw, QByteArray &content)
{
    content.append("Server: IWebCore").append(NEW_LINE);

    auto cookieContent = generateCookieHeaders(raw);
    if(!cookieContent.isEmpty()){
        content.append(cookieContent).append(NEW_LINE);
    }
}

QByteArray generateHeadersContent(IRequestImpl& m_raw, int contentSize)
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

    detail::generateExternalHeadersContent(m_raw.m_respRaw, headersContent);
    return headersContent;
}

}

IResponseRaw::~IResponseRaw()
{
    while(!m_contents.empty()){
        delete m_contents.front();
        m_contents.pop_front();
    }
}

void IResponseRaw::setMime(IHttpMime mime)
{
    this->m_mime = IHttpMimeUtil::toString(mime);
}

void IResponseRaw::setMime(const QString &mime)
{
    this->m_mime = mime;
}

void IResponseRaw::setContent(std::string &&data)
{
    m_contents.push_back(new IStdStringResponseContent(std::move(data)));
}

void IResponseRaw::setContent(const std::string &data)
{
    m_contents.push_back(new IStdStringResponseContent(data));
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
    m_contents.push_back(new IQByteArrayResponseContent(std::move(value)));
}

void IResponseRaw::setContent(const QByteArray &value)
{
    m_contents.push_back(new IQByteArrayResponseContent(value));
}

void IResponseRaw::setContent(const char *value)
{
    m_contents.push_back(new IQByteArrayResponseContent(value));
}

void IResponseRaw::setContent(const QFileInfo &value)
{
    m_contents.push_back(new IFileResponseContent(value.absoluteFilePath()));
}

void IResponseRaw::setContent(const IHttpInvalidWare& ware)
{
    m_contents.push_back(new IInvalidReponseContent(ware));
}

void IResponseRaw::setContent(IResponseContentWare *ware)
{
    m_contents.push_back(ware);
}

std::vector<asio::const_buffer> IResponseRaw::getContent(IRequestImpl& impl)
{
    // prepare
    if(!m_contents.empty() && m_mime.isEmpty()){
        m_mime = m_contents.back()->getSuggestedMime();
    }

    // data
    std::vector<asio::const_buffer> result;
    m_store.emplace_back(detail::generateFirstLine(impl));

    IStringView content{};
    if(!m_contents.empty()){
        content = m_contents.back()->getContent();
    }
    if(content.size() != 0){
        m_store.emplace_back(detail::generateHeadersContent(impl, content.size()));
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


$PackageWebCoreEnd
