#include "IResponseRaw.h"
#include "core/util/IConstantUtil.h"
#include "http/biscuits/IHttpHeader.h"
#include "http/biscuits/IHttpVersion.h"
#include "Http/net/impl/IRequestImpl.h"

#include "http/response/IResponseWare.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "http/response/content/IInvalidReponseContent.h"
#include "http/response/content/IFileResponseContent.h"

$PackageWebCoreBegin

static const IString ServerHeader = "Server: IWebCore\r\n";

namespace detail
{

std::vector<IStringView> generateFirstLine(IRequestImpl& impl)
{
    std::vector<IStringView> ret;
    ret.push_back(IHttpVersionUtil::toString(impl.m_reqRaw.m_httpVersion).m_stringView);
    ret.push_back(IConstantUtil::Space.m_stringView);
    ret.push_back(IHttpStatusUtil::toStringNumber(impl.m_respRaw.m_status).m_stringView);
    ret.push_back(IConstantUtil::Space.m_stringView);
    ret.push_back(IHttpStatusUtil::toStringDescription(impl.m_respRaw.m_status).m_stringView);
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
    if(contentSize != 0){
        headers.insert(IHttpHeader::ContentLength, IString(std::to_string(contentSize)));
        if(!headers.contain(IHttpHeader::ContentType) && !m_raw.m_respRaw.m_mime.isEmpty()){
            headers.insert(IHttpHeader::ContentType, m_raw.m_respRaw.m_mime);
        }
    }

    std::vector<IStringView> ret;
    ret.push_back(ServerHeader.m_stringView);

    std::unordered_map<IString, std::vector<IString>>& headerMap = headers.m_header;
    for(const auto& pair : headerMap){
        ret.push_back(pair.first.m_stringView);
        ret.push_back(IConstantUtil::Comma.m_stringView);
        for(const auto& val : pair.second){
            ret.push_back(val.m_stringView);
        }
        ret.push_back(IConstantUtil::NewLine.m_stringView);
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
    m_headers.insert(std::move(key.solidify()), std::move(value.solidify()));
}

void IResponseRaw::setMime(IHttpMime mime)
{
    this->m_mime = &(IHttpMimeUtil::toString(mime));
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

std::vector<asio::const_buffer> IResponseRaw::getContent(IRequestImpl& impl)
{
    // 这一步是做特殊的处理，将数据封装起来。
    while(!m_contents.empty() && m_contents.back()->m_function){
        m_contents.back()->m_function(*this);
    }

    std::vector<asio::const_buffer> result;

    // first line
    auto firstLine = detail::generateFirstLine(impl);
    for(auto view : firstLine){
        result.push_back(view.toAsioBuffer());
    }

    IStringView content{};
    if(!m_contents.empty()){
        content = m_contents.back()->m_content.m_stringView;
    }

    // headers
    auto headers = detail::generateHeadersContent(impl, content.size());
    for(auto view : headers){
        result.push_back(view.toAsioBuffer());
    }
    result.push_back(IConstantUtil::NewLine.m_stringView.toAsioBuffer());

    // cookies
    auto cookies = detail::generateCookieHeaders(impl);
    for(auto view : cookies){
        result.push_back(view.toAsioBuffer());
    }

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

    // TODO: 先不做, 这个还是有一点复杂， 因为可能涉及到多值的情况
    if(!response.headers().isEmpty()){
        auto keys = response.headers().keys();
        for(const auto& key : keys){
            setHeader(key, response.headers().value(key));
        }
    }

    // NOTE: this break the const constrait, but its safe
    while(!response.m_raw->m_contents.empty()){
        setContent(response.m_raw->m_contents.front());
        response.m_raw->m_contents.pop_front();
    }
}

$PackageWebCoreEnd
