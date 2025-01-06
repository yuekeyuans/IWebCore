#include "IRequestImpl.h"

#include "core/util/IHeaderUtil.h"
#include "core/application/IAsioApplication.h"
#include "core/util/IConstantUtil.h"
#include "core/config/IProfileImport.h"
#include "http/IHttpManage.h"
#include "http/controller/IHttpControllerAction.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/invalid/IHttpInternalErrorInvalid.h"
#include "http/mappings/IHttpAction.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/ISessionJar.h"
#include "http/response/IResponseWare.h"
#include "http/server/ITcpConnection.h"
#include "http/session/ISessionManager.h"
#include <algorithm>
#include <regex>

$PackageWebCoreBegin

IRequestImpl::IRequestImpl(IRequest& self)
    : m_request(self), m_connection(self.m_connection), m_data(self.m_connection.m_data),
      m_headerJar{*this}, m_cookieJar{*this}, m_multiPartJar{*this}
{
    if(ISessionManager::instance()->getSessionWare() != nullptr){
        m_sessionJar = new ISessionJar(m_request.impl());
    }
}

IRequestImpl::~IRequestImpl()
{
    delete m_sessionJar;
}

void IRequestImpl::parseData()
{
    uint length{};
    while(true){
        switch (m_readState) {
        case State::FirstLineState:
            if((length = m_data.getLine())){
                firstLineState(length);
                break;
            }
            if(m_data.isDataFull()){
                setInvalid(IHttpBadRequestInvalid("first line error"));
                break;
            }
            return m_connection.doRead();
        case State::HeaderState:
            if((length = m_data.getBreakSegment())){    // TODO: 明天改这个
                if(headersState(length)){
                    return;
                }
                break;
            }
        case State::ChunckState:
            chunkedState();
            break;
        case ContentState:
            if((length = m_data.getUnparsedLength()) >= m_reqRaw.m_contentLength){
                contentState(m_reqRaw.m_contentLength);
                break;
            }
        case State::EndState:
            return endState();
        }

        if(!m_isValid){
            m_readState = State::EndState;
        }
    }
}

void IRequestImpl::firstLineState(uint length)
{
    IStringView data(m_data.m_data+m_data.m_parsedSize, length);
    m_data.m_parsedSize += length;

    parseFirstLine(data.substr(0, data.length()-2));
    if(!m_isValid){
        return;
    }
    resolveFirstLine();
    m_readState = State::HeaderState;
}

bool IRequestImpl::headersState(uint length)
{
    IStringView data(m_data.m_data+m_data.m_parsedSize, length);
    m_data.m_parsedSize += length;

    parseHeaders(data);
    if(!m_isValid){
        return false;
    }

    resolveHeaders();
    if(!m_isValid){
        return false;
    }

    if(m_reqRaw.m_contentLength){
        m_readState = State::ContentState;
        if(prepareToReadContentLengthData()){
            return true;
        }
    }else if(m_reqRaw.m_isChunked){
        m_readState = State::ChunckState;
        prepareToReadChunkedData();
        return true;
    }else{
        m_readState = State::EndState;
    }
    return false;
}

void IRequestImpl::chunkedState()
{
    auto length = m_data.m_buffer.size();
    auto data = IStringView(static_cast<const char*>(m_data.m_buffer.data().data()), length);
    parseChunkedData(data);

    if(m_isValid){
        resolvePayload();
    }

    m_readState = State::EndState;
}

void IRequestImpl::contentState(std::size_t length)
{
    if(m_data.m_bodyInData){
        m_reqRaw.m_body = IStringView(m_data.m_data+m_data.m_parsedSize, length);
        m_data.m_parsedSize += length;
    }else{
        m_reqRaw.m_body = IStringView(asio::buffer_cast<const char*>(m_data.m_buffer.data()), length);
    }

    resolvePayload();
    m_readState = State::EndState;
}

void IRequestImpl::endState()
{
    parseAction();
    auto application = dynamic_cast<IAsioApplication*>(IApplicationInterface::instance());
    asio::post(application->ioContext(), [=](){
        this->m_action->invoke(m_request);
    });
}

bool IRequestImpl::prepareToReadContentLengthData()
{
    auto unparsedLength = m_data.getUnparsedLength();
    if(unparsedLength >= m_reqRaw.m_contentLength){
        return false;
    }

    if(m_data.m_parsedSize + m_reqRaw.m_contentLength < m_data.m_maxSize){
        if(unparsedLength < m_reqRaw.m_contentLength){
            m_connection.doReadStreamBy(m_reqRaw.m_contentLength-unparsedLength, true);
            return true;
        }
    }else{
        m_data.m_bodyInData = false;
        auto data = asio::buffer_cast<char*>(m_data.m_buffer.prepare(m_reqRaw.m_contentLength));
        memcpy(data, m_data.m_data + m_data.m_parsedSize, unparsedLength); // 拷贝数据
        m_data.m_buffer.commit(unparsedLength);
        m_connection.doReadStreamBy(m_reqRaw.m_contentLength-unparsedLength, false);
        return true;
    }
    return false;
}

bool IRequestImpl::prepareToReadChunkedData()
{
    m_data.m_bodyInData = false;
    m_connection.doReadStreamUntil("\r\n\r\n");
    return true;
}

void IRequestImpl::parseFirstLine(IStringView line)
{
    static const std::regex URI_REGEX(R"(^(\/[\w\-._~%!$&'()*+,;=:@/]*(\?[\w\-._~%!$&'()*+,;=:@/?]*)?|https?:\/\/[\w\-._~%!$&'()*+,;=:@]+\.[\w\-._~%!$&'()*+,;=:@]+(:\d+)?(\/[\w\-._~%!$&'()*+,;=:@/]*(\?[\w\-._~%!$&'()*+,;=:@/?]*)?)?|[*])$)");
    static $UInt urlMaxLength{"/http/urlMaxLength", 1024*8};
    if(line.length() >= *urlMaxLength){
        return setInvalid(IHttpInvalidWare(IHttpStatus::URI_TOO_LONG_414));
    }

    int pos{};

    // method
    auto index = line.find_first_of(' ', pos);
    if(index == std::string::npos){
        return setInvalid(IHttpBadRequestInvalid("can not resolve current method type"));
    }
    auto method = line.substr(pos, index);
    m_reqRaw.m_method = IHttpMethodUtil::toMethod(method);
    if(m_reqRaw.m_method == IHttpMethod::UNKNOWN){
        return setInvalid(IHttpInvalidWare(IHttpStatus::METHOD_NOT_ALLOWED_405));
    }
    pos = index + 1;

    // path
    index = line.find_first_of(' ', pos);
    if(index == std::string_view::npos){
        return setInvalid(IHttpBadRequestInvalid("request path is not correct"));
    }
    m_reqRaw.m_rawUrl = line.substr(pos, index-pos);
    if (!std::regex_match(m_reqRaw.m_rawUrl.begin(), m_reqRaw.m_rawUrl.end(), URI_REGEX)) {
        return setInvalid(IHttpBadRequestInvalid("url not valid"));
    }
    pos = index +1;

    // version
    m_reqRaw.m_httpVersion = IHttpVersionUtil::toVersion(line.substr(pos));
    if(m_reqRaw.m_httpVersion == IHttpVersion::UNKNOWN){
        return setInvalid(IHttpInvalidWare(IHttpStatus::HTTP_VERSION_NOT_SUPPORTED_505));
    }
}

void IRequestImpl::resolveFirstLine()
{
    auto index = m_reqRaw.m_rawUrl.find_first_of('?');
    if(index == std::string_view::npos){
        m_reqRaw.m_rawPath = m_reqRaw.m_rawUrl;
        m_reqRaw.m_url = QByteArray::fromPercentEncoding(QByteArray(m_reqRaw.m_rawUrl.data(), m_reqRaw.m_rawUrl.length()));
        return;
    }

    m_reqRaw.m_rawPath = m_reqRaw.m_rawUrl.substr(0, index);
    m_reqRaw.m_url = QByteArray::fromPercentEncoding(QByteArray(m_reqRaw.m_rawUrl.data(), m_reqRaw.m_rawUrl.length()));

    m_reqRaw.m_rawPathArgs = m_reqRaw.m_rawUrl.substr(index+1);
    parseUrlEncodedData(m_reqRaw.m_rawPathArgs, false);
}

void IRequestImpl::parseHeaders(IStringView data)
{
    auto lines = data.split("\r\n");
    while(!lines.empty()){
        auto line = lines.takeLast();
        if(!line.empty()){
            if(line.startWith("\t") || line.startWith("  ")){
                if(lines.empty()){
                    return setInvalid(IHttpBadRequestInvalid("header invalid"));
                }
                auto newLine = stash(lines.takeLast().toStdString() + line.trimmed().toStdString());
                lines.push_back(newLine);
            }else{
                parseHeader(line);
            }
        }
    }
}

void IRequestImpl::parseHeader(IStringView line)
{
    static $UInt headerMaxLength("/http/headerMaxLength", 1024*8);
    if(line.length() > *headerMaxLength){
        return setInvalid(IHttpInvalidWare(IHttpStatus::REQUEST_HEADER_FIELDS_TOO_LARGE_431));
    }
    auto index = line.find(':');
    if(index == std::string_view::npos){
        return setInvalid(IHttpBadRequestInvalid("server do not support headers item multiline, or without key/value pair"));  // SEE: 默认不支持 headers 换行书写
    }
    auto key = line.substr(0, index).trimmed();
    auto value = line.substr(index+1).trimmed();

    if(key.equalIgnoreCase(IHttpHeader::Cookie)){
        return parseCookie(value);
    }
    if(m_headerJar.containRequestHeaderKey(key)){
        return m_request.setInvalid(IHttpBadRequestInvalid("header duplicated"));
    }
    m_reqRaw.m_headers[key] = value;
}

void IRequestImpl::parseCookie(IStringView cookie)
{
    auto pairs = cookie.split(IConstantUtil::Semicolon);
    for(auto pair : pairs){
        auto val = pair.trimmed();
        if(!val.empty()){
            auto args = val.split(IConstantUtil::Equal);
            if(args.length() == 1){
                m_reqRaw.m_cookies.insertMulti(stash(args.first()), stash(args.first()));
            }else{
                m_reqRaw.m_cookies.insertMulti(stash(args.first()), stash(args.last()));
            }
        }
    }
}

void IRequestImpl::resolveHeaders()
{
    const auto& encoding = m_headerJar.getRequestHeaderValue(IHttpHeader::TransferEncoding);
    if(encoding.length()){
        if(encoding.equalIgnoreCase("chunked")){
            m_reqRaw.m_isChunked = true;
        }
    }
    const auto& contentLength = m_headerJar.getRequestHeaderValue(IHttpHeader::ContentLength);
    if(contentLength.length()){
        if(m_reqRaw.m_isChunked){
            return setInvalid(IHttpBadRequestInvalid("ContentLength and chunked exist at same time"));
        }
        bool ok;
        m_reqRaw.m_contentLength = contentLength.value<int>(ok);
        if(!ok){
            return setInvalid(IHttpBadRequestInvalid("ContentLength error"));
        }
        static $UInt bodyMaxLength("/http/bodyMaxLength", 4194304);
        if(m_reqRaw.m_contentLength > *bodyMaxLength){
            return setInvalid(IHttpBadRequestInvalid("Content Length too large to accept"));
        }
    }

    const auto& contentType = m_headerJar.getRequestHeaderValue(IHttpHeader::ContentType);
    if(contentType.length()){
        m_reqRaw.m_mime = IHttpMimeUtil::toMime(contentType);
        if(m_reqRaw.m_mime == IHttpMime::MULTIPART_FORM_DATA){
            m_multipartBoundary = getBoundary(contentType);
            if(m_multipartBoundary.empty()){
                return setInvalid(IHttpBadRequestInvalid("multipart request has no boundary"));
            }
            m_multipartBoundaryEnd = stash(m_multipartBoundary.toQByteArray() + "--");
        }
    }
}

void IRequestImpl::resolvePayload()
{
    switch (m_reqRaw.m_mime) {
    case IHttpMime::MULTIPART_FORM_DATA:
        parseMultiPartData(m_reqRaw.m_body);
        break;
    case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
        parseUrlEncodedData(m_reqRaw.m_body, true);
        break;
    case IHttpMime::APPLICATION_JSON:
    case IHttpMime::APPLICATION_JSON_UTF8:
        parseJsonData(m_reqRaw.m_body);
        break;
    default:
        break;
    }
}

void IRequestImpl::parseUrlEncodedData(IStringView view, bool isBody)
{
    auto parts = view.split("&");
    for(auto part : parts){
        if(part.empty()){
            continue;
        }
        IStringViewList pair = part.split("=");
        if(pair.length() != 2){
            setInvalid(IHttpBadRequestInvalid("form data error"));
            return;
        }
        pair.first().trimmed();
        pair.last().trimmed();
        auto key = stash(QByteArray::fromPercentEncoding(QByteArray(pair.first().data(), pair.first().length())));
        auto value = stash(QByteArray::fromPercentEncoding(QByteArray(pair.last().data(), pair.last().length())));
        if(isBody){
            m_reqRaw.m_forms[key] = value;
        }else{
            m_reqRaw.m_paths[key] = value;
        }
    }
}

void IRequestImpl::parseJsonData(IStringView data)
{
    m_reqRaw.m_json = IJson::parse(data.begin(), data.end(), nullptr, true);
    if(m_reqRaw.m_json.is_discarded()){
        setInvalid(IHttpBadRequestInvalid("json error"));
    }
}

void IRequestImpl::parseMultiPartData(IStringView data)
{
    data = data.trimmed();
    if(!data.startWith(m_multipartBoundary)){
        return setInvalid(IHttpBadRequestInvalid("multipart start error"));
    }
    data = data.substr(m_multipartBoundary.length()).trimmed();

    auto endPos = data.find(m_multipartBoundaryEnd);
    if(endPos == IStringView::npos){
        return setInvalid(IHttpBadRequestInvalid("multipart end error"));
    }
    data = data.substr(0, endPos);

    auto values = data.split(m_multipartBoundary);
    for(IStringView value : values){
        if(!value.trimmed().empty()){
            IMultiPart part(value, &m_request);
            if(!part.isValid()){
                return;
            }
            m_reqRaw.m_multiParts.emplace_back(std::move(part));
        }
    }
}

void IRequestImpl::parseAction()
{
    m_action = IHttpManage::instance()->getAction(m_request);
}

IStringView IRequestImpl::getBoundary(IStringView data)
{
    static const std::string prefix = "boundary=";
    auto index = data.find(prefix);
    if(index == std::string_view::npos){
        return {};
    }

    auto view = data.substr(index + prefix.length());
    if(view.empty()){
        return {};
    }

    if(view.startWith("\"") && view.endWith("\"")){
        view = view.substr(1, view.length()-2);
    }
    return stash("--" + view.toStdString());
}

void IRequestImpl::parseChunkedData(IStringView data) {
    std::string result;
    result.reserve(data.length());
    std::size_t pos{};
    while(true){
        auto end = data.find("\r\n", pos);
        if(end == std::string_view::npos){
            return setInvalid(IHttpBadRequestInvalid("Invalid chunked data: missing chunk size delimiter"));
        }
        std::string_view chunkedSize = data.substr(pos, end - pos);
        size_t chunk_size = 0;
        try {
            chunk_size = std::stoul(std::string(chunkedSize), nullptr, 16);
        } catch (...) {
            return setInvalid(IHttpBadRequestInvalid("Invalid chunk size:"));
        }
        pos = end + 2;
        if(chunk_size == 0){
            pos+=2;
            break;
        }
        if(pos + chunk_size > data.size()){
            return setInvalid(IHttpBadRequestInvalid("Invalid chunked data: missing chunk terminator"));
        }

        result.append(data.substr(pos, chunk_size));
        pos += chunk_size;
        if(!data.substr(pos, 2).equalIgnoreCase("\r\n")){
            return setInvalid(IHttpBadRequestInvalid("Invalid chunked data: missing chunk terminator"));
        }
        pos += 2;
    }
    while (pos < data.size()){
        auto end = data.find("\r\n", pos);
        if(end == std::string_view::npos){
            return setInvalid(IHttpBadRequestInvalid("Invalid chunked data: incomplete trailer"));
        }
        if(end == pos){
            pos += 2;
            break;
        }
        auto line = data.substr(pos, end-pos);
        auto colonPos = line.find(":");
        auto key = line.substr(0, colonPos).trimmed();
        auto value = line.substr(colonPos + 1).trimmed();
        m_reqRaw.m_headers[key] = value;
        pos = end + 2;
    }
    m_reqRaw.m_contentLength = result.length();
    m_reqRaw.m_body = stash(result);
}

void IRequestImpl::setInvalid(const IHttpInvalidWare& ware)
{
    m_isValid = false;
    m_respRaw.setMime(IHttpMime::TEXT_PLAIN_UTF8);
    m_respRaw.setContent(ware);
}

void IRequestImpl::setResponseWare(const IResponseWare &ware)
{
    m_isValid &= ware.m_raw->m_isValid;
    m_respRaw.setResponseWare(ware);
}

$PackageWebCoreEnd
