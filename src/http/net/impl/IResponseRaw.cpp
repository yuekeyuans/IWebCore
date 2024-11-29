#include "IResponseRaw.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "Http/net/impl/IRequestImpl.h"

#include "http/response/IResponseWare.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/response/content/IQStringResponseContent.h"
#include "http/response/content/IQByteArrayResponseContent.h"
#include "http/response/content/IInvalidReponseContent.h"
#include "http/response/content/IFileResponseContent.h"
#include "http/response/content/IStdStringResponseContent.h"
#include "http/response/content/IStrinigViewResponseContent.h"
#include "http/response/content/IJsonResponseContent.h"
#include "http/response/content/IInvalidReponseContent.h"

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

// TODO: 这里之后补充
QByteArray generateHeadersContent(IRequestImpl& m_raw, int contentSize)
{
    if(contentSize != 0){
//        m_raw.m_headerJar.setResponseHeader(IHttpHeader::ContentLength, QString::number(contentSize));
//        if(!m_raw.m_headerJar.containResponseHeaderKey(IHttpHeader::ContentType)
//                && !m_raw.m_respRaw.m_mime.isEmpty()){
//            m_raw.m_headerJar.setResponseHeader(IHttpHeader::ContentType, m_raw.m_respRaw.m_mime);
//        }
    }

//    QByteArray headersContent;
//    auto keys = m_raw.m_respRaw.m_headers.uniqueKeys();
//    for(const auto& key : keys){
//        auto values = m_raw.m_respRaw.m_headers.values(key);
//        headersContent.append(key).append(":").append(values.join(";")).append(NEW_LINE);
//    }

//    detail::generateExternalHeadersContent(m_raw.m_respRaw, headersContent);
//    return headersContent;

    return {};
}

}

IResponseRaw::~IResponseRaw()
{
    while(!m_contents.empty()){
        delete m_contents.front();
        m_contents.pop_front();
    }
}

void IResponseRaw::setHeader(IString key, IString value)
{
    m_headers.insert(std::move(key), std::move(value));
}

void IResponseRaw::setMime(IHttpMime mime)
{
    this->m_mime = IHttpMimeUtil::toString(mime);
}

void IResponseRaw::setMime(IString &&mime)
{
    this->m_mime = std::move(mime);
}

void IResponseRaw::setContent(IJson &&data)
{
    setContent(new IJsonResponseContent(std::move(data)));
}

void IResponseRaw::setContent(const IJson &data)
{
    setContent(new IJsonResponseContent(data));
}

void IResponseRaw::setContent(std::string &&data)
{
    setContent(new IStdStringResponseContent(std::move(data)));
}

void IResponseRaw::setContent(const std::string &data)
{
    setContent(new IStdStringResponseContent(data));
}

void IResponseRaw::setContent(QString &&value)
{
    setContent(new IQStringResponseContent(std::move(value)));
}

void IResponseRaw::setContent(const QString &value)
{
    setContent(new IQStringResponseContent(value));
}

void IResponseRaw::setContent(QByteArray &&value)
{
    setContent(new IQByteArrayResponseContent(std::move(value)));
}

void IResponseRaw::setContent(const QByteArray &value)
{
    setContent(new IQByteArrayResponseContent(value));
}

void IResponseRaw::setContent(const char *value)
{
    setContent(new IQByteArrayResponseContent(value));
}

void IResponseRaw::setContent(IStringView data)
{
    setContent(new IStrinigViewResponseContent(data));
}

void IResponseRaw::setContent(const QFileInfo &value)
{
    setContent(new IFileResponseContent(value.absoluteFilePath()));
}

void IResponseRaw::setContent(const IHttpInvalidWare& ware)
{
    setContent(new IInvalidReponseContent(ware));
}

void IResponseRaw::setContent(IResponseContentWare *ware)
{
    m_contents.push_back(ware);
    auto invalidWare = dynamic_cast<IInvalidReponseContent*>(ware);
    if(invalidWare){
        this->m_isValid = false;
        this->m_status = invalidWare->m_ware.status;
        this->m_mime = invalidWare->getSuggestedMime(); // TODO: 感觉这里不对
    }

    if(ware->m_excess){
        ware = ware->m_excess;
        ware->m_excess = nullptr;
        setContent(ware);
    }
}

std::vector<asio::const_buffer> IResponseRaw::getContent(IRequestImpl& impl)
{
    std::vector<asio::const_buffer> result;

    if(!m_contents.empty() && m_mime.isEmpty()){
        m_mime = m_contents.back()->getSuggestedMime();
    }

    IStringView firstLine = stash(detail::generateFirstLine(impl));
    result.push_back(firstLine.toAsioBuffer());

    IStringView content{};
    if(!m_contents.empty()){
        content = m_contents.back()->getContent();
    }
    if(content.size() != 0){
        result.push_back(stash(detail::generateHeadersContent(impl, content.size())).toAsioBuffer());
    }
    result.push_back(asio::const_buffer(NEW_LINE, 2));

    if(!content.empty()  && impl.m_reqRaw.m_method != IHttpMethod::HEAD){
        result.push_back(content.toAsioBuffer());
    }

    return result;
}

void IResponseRaw::setResponseWare(IResponseWare && ware)
{
    setResponseWare(ware);
}

void IResponseRaw::setResponseWare(IResponseWare &response)
{
    if(!response.mime().isEmpty()){
        m_mime = response.mime();
    }
    if(response.status() != m_status){
        m_status = response.status();
    }

    // TODO: 先不做, 这个还是有一点复杂， 因为可能涉及到多值的情况
    if(!response.headers().isEmpty()){
        auto keys = response.headers().keys();
        for(const auto& key : keys){
            setHeader(key, response.headers().value(key));
        }
    }
    while(!response.m_raw->m_contents.empty()){
        setContent(response.m_raw->m_contents.front());
        response.m_raw->m_contents.pop_front();
    }
}

$PackageWebCoreEnd
