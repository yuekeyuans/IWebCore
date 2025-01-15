#include "IResponseRaw.h"
#include "core/util/IConstantUtil.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "http/detail/IRequestImpl.h"
#include "http/response/IResponseWare.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/response/content/IInvalidReponseContent.h"
#include "http/response/content/IFileResponseContent.h"
#include "tcp/ITcpConnection.h"

$PackageWebCoreBegin

static const IString ServerHeader = "Server: IWebCore\r\n";

namespace detail
{
std::vector<IStringView> generateFirstLine(IRequestImpl& impl)
{
    std::vector<IStringView> ret;
    ret.push_back(IHttpVersionUtil::toString(impl.m_reqRaw.m_httpVersion).m_view);
    ret.push_back(IConstantUtil::Space.m_view);
    ret.push_back(IHttpStatusUtil::toStringNumber(impl.m_respRaw.m_status).m_view);
    ret.push_back(IConstantUtil::Space.m_view);
    ret.push_back(IHttpStatusUtil::toStringDescription(impl.m_respRaw.m_status).m_view);
    ret.push_back(IConstantUtil::NewLine);

    return ret;
}

std::vector<IStringView> generateCookieHeaders(IRequestImpl& impl)
{
    std::vector<IStringView> ret;
    for(const auto& cookie : impl.m_respRaw.m_cookies){
        auto vals = cookie.toHeaderString();
        for(auto val : vals){
            ret.push_back(val);
        }
    }

    return ret;
}

std::vector<IStringView> generateHeadersContent(IRequestImpl& m_raw, int contentSize)
{
    auto& headers = m_raw.m_respRaw.m_headers;

    headers.insert(IHttpHeader::ContentLength, IString(std::to_string(contentSize)));
    if(contentSize != 0){
        if(!headers.contain(IHttpHeader::ContentType) && !m_raw.m_respRaw.m_mime.isEmpty()){
            headers.insert(IHttpHeader::ContentType, m_raw.m_respRaw.m_mime);
        }
    }

    if(m_raw.m_connection.m_keepAlive){
        headers.insert(IHttpHeader::Connection, "keep-alive");
        headers.insert(IHttpHeader::KeepAlive, "timeout=10, max=50");
    }

    std::vector<IStringView> ret;
    ret.push_back(ServerHeader.m_view);

    for(const auto& pair : headers.m_header){
        ret.push_back(pair.first);
        ret.push_back(IConstantUtil::CommaSpace.m_view);
        ret.push_back(pair.second);
        ret.push_back(IConstantUtil::NewLine.m_view);
    }

    return ret;
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

void IResponseRaw::setContent(const IHttpInvalidWare& ware)
{
    m_status = ware.status;
    setContent(new IInvalidReponseContent(ware));
}

void IResponseRaw::setContent(IResponseContent *ware)
{
    m_contents.push_back(ware);

    auto invalidWare = dynamic_cast<IInvalidReponseContent*>(ware);
    if(invalidWare){
        this->m_isValid = false;
    }
}

void IResponseRaw::setCookie(ICookiePart &&cookie)
{
    m_cookies.emplace_back(std::move(cookie));
}

void IResponseRaw::setCookie(const ICookiePart &cookie)
{
    m_cookies.push_back(cookie);
}

void IResponseRaw::setCookie(const IString &key, const IString &value)
{
    m_cookies.emplace_back(key, value);
}

std::vector<asio::const_buffer> IResponseRaw::getContent(IRequestImpl& impl)
{
    // 这一步是做特殊的处理，将数据封装起来。
    while(!m_contents.empty() && m_contents.back()->m_function){
        m_contents.back()->m_function(*(m_contents.back()), *this);
    }

    std::vector<asio::const_buffer> result;

    // first line
    auto firstLine = detail::generateFirstLine(impl);
    for(auto view : firstLine){
        result.push_back(view.toAsioBuffer());
    }

    IStringView content{};
    if(!m_contents.empty()){
        content = m_contents.back()->m_content.m_view;
    }

    // headers
    auto headers = detail::generateHeadersContent(impl, content.size());
    for(auto view : headers){
        result.push_back(view.toAsioBuffer());
    }

    // cookies
    auto cookies = detail::generateCookieHeaders(impl);
    for(auto view : cookies){
        result.push_back(view.toAsioBuffer());
    }

    result.push_back(IConstantUtil::NewLine.m_view.toAsioBuffer());
    if(!content.empty()  && impl.m_reqRaw.m_method != IHttpMethod::HEAD){
        result.push_back(content.toAsioBuffer());
    }
    return result;
}

void IResponseRaw::setResponseWare(const IResponseWare &response)
{
    if(!response.mime().isEmpty()){
        m_mime = response.mime();
    }
    if(response.status() != m_status){
        m_status = response.status();
    }

    if(!response.headers().isEmpty()){
        for(auto& [key, val] : response.headers().m_header){
            setHeader(key, val);
        }
    }

    if(!response.m_raw->m_cookies.empty()){
        for(auto cookie : response.m_raw->m_cookies){
            this->m_cookies.push_back(cookie);
        }
        response.m_raw->m_cookies.clear();
    }

    // NOTE: this break the const constrait, but its safe
    while(!response.m_raw->m_contents.empty()){
        setContent(response.m_raw->m_contents.front());
        response.m_raw->m_contents.pop_front();
    }
}

$PackageWebCoreEnd
