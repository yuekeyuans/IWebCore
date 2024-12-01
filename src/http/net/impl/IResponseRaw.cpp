#include "IResponseRaw.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "Http/net/impl/IRequestImpl.h"

#include "http/response/IResponseWare.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/response/content/IInvalidReponseContent.h"
#include "http/response/content/IFileResponseContent.h"
#include "http/response/content/IJsonResponseContent.h"
#include "http/response/content/IStringResponseContent.h"

$PackageWebCoreBegin

static constexpr char NEW_LINE[] = "\r\n";
static const IString NewLine = "\r\n";
static const IString SPACE = " ";
static const IString COMMA = ": ";

namespace detail
{

std::vector<IStringView> generateFirstLine(IRequestImpl& impl)
{
    std::vector<IStringView> ret;
    ret.push_back(IHttpVersionUtil::toString(impl.m_reqRaw.m_httpVersion).m_stringView);
    ret.push_back(SPACE.m_stringView);
    ret.push_back(IHttpStatusUtil::toStringNumber(impl.m_respRaw.m_status).m_stringView);
    ret.push_back(SPACE.m_stringView);
    ret.push_back(IHttpStatusUtil::toStringDescription(impl.m_respRaw.m_status).m_stringView);
    ret.push_back(NewLine);

    return ret;
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
//    content.append("Server: IWebCore").append(NEW_LINE);

//    auto cookieContent = generateCookieHeaders(raw);
//    if(!cookieContent.isEmpty()){
//        content.append(cookieContent).append(NEW_LINE);
//    }
}

std::vector<IStringView> generateHeadersContent(IRequestImpl& m_raw, int contentSize)
{
    auto& headers = m_raw.m_respRaw.m_headers;
    if(contentSize != 0){
        headers.insert(IHttpHeader::ContentLength, IString(std::to_string(contentSize)));
        if(headers.contain(IHttpHeader::ContentType)
                && !m_raw.m_respRaw.m_mime.isEmpty()){
            headers.insert(IHttpHeader::ContentDisposition, m_raw.m_respRaw.m_mime);
        }
    }

    std::vector<IStringView> ret;
    std::unordered_map<IString, std::vector<IString>>& headerMap = headers.m_header;
    for(const auto& pair : headerMap){
        ret.push_back(pair.first.m_stringView);
        ret.push_back(COMMA.m_stringView);
        for(const auto& val : pair.second){
            ret.push_back(val.m_stringView);
        }
        ret.push_back(NewLine.m_stringView);
    }

    return ret;

//    detail::generateExternalHeadersContent(m_raw.m_respRaw, headersContent);
//    return headersContent;
//    return {};
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

void IResponseRaw::setContent(IString &&value)
{
    setContent(new IStringResponseContent(std::move(value)));
}

void IResponseRaw::setContent(const IString &value)
{
    setContent(new IStringResponseContent(value));
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
        // TODO:
//        this->m_status = invalidWare->m_ware.status;
//        this->m_mime = invalidWare->getSuggestedMime(); // TODO: 感觉这里不对
    }

    if(ware->m_excess != nullptr){
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

    // first line
    auto firstLine = detail::generateFirstLine(impl);
    for(auto view : firstLine){
        result.push_back(view.toAsioBuffer());
    }

    IStringView content{};
    if(!m_contents.empty()){
        content = m_contents.back()->getContent();
    }

    auto headers = detail::generateHeadersContent(impl, content.size());
    for(auto view : headers){
        result.push_back(view.toAsioBuffer());
    }
    result.push_back(NewLine.m_stringView.toAsioBuffer());

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
