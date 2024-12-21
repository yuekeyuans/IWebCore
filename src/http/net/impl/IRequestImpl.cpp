#include "IRequestImpl.h"

#include "core/util/IHeaderUtil.h"
#include "core/application/IAsioApplication.h"
#include "core/util/IConstantUtil.h"
#include "core/config/IProfileImport.h"
#include "http/IHttpManage.h"
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
    int line[2];
    while(true){
        switch (m_readState) {
        case State::FirstLineState:
            if(!m_data.getLine(line)){
                return m_connection.doRead();
            }
            firstLineState(IStringView(m_data.m_data + line[0], line[1]));
            break;
        case State::HeaderState:
            if(!m_data.getBreakSegment(line)){
                return m_connection.doRead();
            }
            headersState(IStringView(m_data.m_data + line[0], line[1]));
            break;
        case State::HeaderGapState:
            if(!headerGapState()){
                return;
            }
            break;
        case BodyState:
            bodyState();
            break;
        case State::EndState:
            return endState();
        }

        if(!m_isValid){
            m_readState = State::EndState;
        }
    }
}

void IRequestImpl::firstLineState(IStringView data)
{
    m_data.m_parsedSize += data.length();
    parseFirstLine(data.substr(0, data.length()-2));
    if(!m_isValid){
        return;
    }

    resolveFirstLine();
    m_readState = State::HeaderState;
}

void IRequestImpl::headersState(IStringView data)
{
    m_data.m_parsedSize += data.length();

    parseHeaders(data);
    if(!m_isValid){
        return;
    }

    resolveHeaders();
    if(!m_isValid){
        return;
    }

    if(m_reqRaw.m_contentLength || !m_multipartBoundary.empty()){
        m_readState = State::HeaderGapState;
    }else{
        m_readState = State::EndState;
    }
}

// TODO: 这个感觉不太对， 之后再看，现在先不看这个了。
bool IRequestImpl::headerGapState()
{
    m_readState = BodyState;
    int readLength = m_data.m_readSize - m_data.m_parsedSize;
    if(m_reqRaw.m_contentLength){
        if(m_data.m_parsedSize + m_reqRaw.m_contentLength < m_data.m_maxSize){   // 表示可以使用 data 空间
            if(readLength == m_reqRaw.m_contentLength){
                return true;        // 表示可以直接解析
            }
            m_connection.doRead(); // 继续读取
        }else{
            m_bodyInData = false;   // 表示数据存放在 buffer 中
            auto data = asio::buffer_cast<char*>(m_data.m_buffer.prepare(m_reqRaw.m_contentLength));
            memcpy(data, m_data.m_data + m_data.m_parsedSize, readLength); // 拷贝数据
            m_data.m_buffer.commit(readLength);
            m_connection.doReadStreamBy(m_reqRaw.m_contentLength-readLength);
        }
    }else if(!m_multipartBoundary.empty()){
        IStringView view(m_data.m_data + m_data.m_parsedSize, readLength);
        if(view.find(m_multipartBoundaryEnd) != std::string_view::npos){
            return true;
        }

        m_bodyInData = false;
        auto data = asio::buffer_cast<char*>(m_data.m_buffer.prepare(readLength * 2));
        memcpy(data, m_data.m_data + m_data.m_parsedSize, readLength); // 拷贝数据
        m_connection.doReadStreamBy(m_reqRaw.m_contentLength-readLength);
        m_data.m_buffer.commit(readLength);
        m_connection.doReadStreamUntil(m_multipartBoundaryEnd);
    }
    return false;
}

void IRequestImpl::bodyState()
{
    if(m_reqRaw.m_contentLength){
        resolveBodyContent();
    }else if(!m_multipartBoundary.empty()){
        resolveMultipartContent();
    }

    if(m_isValid){
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

    m_readState = State::EndState;
}

void IRequestImpl::endState()
{
    auto application = dynamic_cast<IAsioApplication*>(IApplicationInterface::instance());
    asio::post(application->ioContext(), [=](){
        auto action = IHttpManage::instance()->getAction(m_request);
        action->invoke(m_request);
    });
}

void IRequestImpl::parseFirstLine(IStringView line)
{
    static $UInt urlMaxLength{"/http/urlMaxLength", 1024*8};
    if(line.length() >= *urlMaxLength){
        return setInvalid(IHttpInvalidWare(IHttpStatus::URI_TOO_LONG_414));
    }

    int pos = 0;
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

    // path TODO: 检查一下url 是否合规
    index = line.find_first_of(' ', pos);
    if(index == std::string_view::npos){
        return setInvalid(IHttpBadRequestInvalid("request path is not correct"));
    }
    m_reqRaw.m_rawUrl = line.substr(pos, index-pos);
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
    m_reqRaw.m_headers.insert(key, value);
}

void IRequestImpl::resolveHeaders()
{
    const auto& encoding = m_headerJar.getRequestHeaderValue(IHttpHeader::TransferEncoding);
    if(encoding == "chunked"){
        return setInvalid(IHttpInternalErrorInvalid("transferEncond:chunked not supported now"));
    }

    const auto& contentLength = m_headerJar.getRequestHeaderValue(IHttpHeader::ContentLength);
    if(&contentLength != &IConstantUtil::Empty){
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
    if(&contentType != &IConstantUtil::Empty){
        m_reqRaw.m_mime = IHttpMimeUtil::toMime(contentType);
        if(m_reqRaw.m_mime == IHttpMime::MULTIPART_FORM_DATA){
            m_multipartBoundary = getBoundary(contentType);
            if(m_multipartBoundary.empty()){
                return setInvalid(IHttpBadRequestInvalid("multipart request has no boundary"));
            }
            m_multipartBoundaryEnd = stash(m_multipartBoundary.toQByteArray() + "--");
        }
    }

    resolveCookieHeaders();
}

void IRequestImpl::resolveCookieHeaders()
{
    auto cookies = m_reqRaw.m_headers.values(IHttpHeader::Cookie);
    for(const auto& cookie : cookies){
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
}

// TODO:
//void IRequestImpl::resolvePathProcessor()
//{
//    if(m_raw->m_method == IHttpMethod::OPTIONS){
//        m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Option;
//        return;
//    }

//    // TODO: 这里需要看一下
//    static auto controllerManage = IHttpManage::instance();
////    static const bool isUrlActionEnabled = controllerManage->isUrlActionNodeEnabled();     // process as dynamic server first
//    if(true){
//        m_raw->m_processer.node = controllerManage->getAction(*m_request);
//        if(m_raw->m_processer.node != nullptr){
//            m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Function;
//            return;
//        }
//    }

//    static bool isStaticFileEnabled = controllerManage->isStaticFileActionPathEnabled();        // process as static file server then
//    if(isStaticFileEnabled && m_request->method() == IHttpMethod::GET){
//        m_raw->m_processer.path = controllerManage->getStaticFileActionPath(*m_request);
//        if(!m_raw->m_processer.path.isEmpty()){
//            m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Path;
//            return;
//        }

//        static $Bool handleDir{"/http/fileService/folderHandled", false};
//        if(*handleDir){
//            m_raw->m_processer.entries = controllerManage->getStaticFolderActionPath(*m_request);
//            if(!m_raw->m_processer.entries.isEmpty()){
//                m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Directory;
//                return;
//            }
//        }
//    }

//    QString info = m_request->url().toQString() + " " + IHttpMethodUtil::toString(m_request->method()) + " has no function to handle";
//    m_request->setInvalid(IHttpNotFoundInvalid(std::move(info)));
//}

void IRequestImpl::resolveBodyContent()
{
    if(m_bodyInData){
        auto readSize = m_data.m_readSize - m_data.m_parsedSize;
        if(m_reqRaw.m_contentLength != readSize){
            return setInvalid(IHttpBadRequestInvalid("content-length mismatch"));
        }
        m_reqRaw.m_body = IStringView(m_data.m_data + m_data.m_parsedSize, readSize);
    }else{
        if(m_reqRaw.m_contentLength != m_data.m_buffer.size()){
            return setInvalid(IHttpBadRequestInvalid("content-length mismatch"));
        }
        m_reqRaw.m_body = IStringView(asio::buffer_cast<const char*>(m_data.m_buffer.data()), m_data.m_buffer.size());
    }
}

void IRequestImpl::resolveMultipartContent()
{
    if(m_bodyInData){
        m_reqRaw.m_body = IStringView(m_data.m_data + m_data.m_parsedSize, m_data.m_readSize - m_data.m_parsedSize);
    }else{
        m_reqRaw.m_body = IStringView(asio::buffer_cast<const char*>(m_data.m_buffer.data()), m_data.m_buffer.size());
    }
    if(!m_reqRaw.m_body.m_stringView.endWith(m_multipartBoundaryEnd)){
        setInvalid(IHttpBadRequestInvalid("multipart data do not have end tag"));
    }
}

void IRequestImpl::parseUrlEncodedData(IStringView view, bool isBody)
{
    IStringView data = stash(QByteArray::fromPercentEncoding(QByteArray(view.data(), view.length())));
    int pos{};
    for(;;){
        auto index = data.find_first_of("&", pos);
        if(index == IStringView::npos){
            break;
        }
        auto value = data.substr(pos, index).trimmed();
        auto partIndex = value.find_first_of('=');
        if(partIndex == IStringView::npos){
            setInvalid(IHttpBadRequestInvalid("the parameters in body should be pair"));
        }
        if(isBody){
            m_reqRaw.m_forms[value.substr(0, partIndex).trimmed()] = value.substr(partIndex + 1).trimmed();
        }else{
            m_reqRaw.m_paths[value.substr(0, partIndex).trimmed()] = value.substr(partIndex + 1).trimmed();
        }
        pos = index+1;
    }
}

// TODO: check it;
void IRequestImpl::parseJsonData(IStringView data)
{
//    auto val = IJsonUtil::toJsonValue(data);
//    if(!val){
//        m_request->setInvalid(IHttpBadRequestInvalid("parse json failed"));
//    }else{
//        m_raw->m_requestJson = *std::move(val);
//    }
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

//void IRequestImplHelper::checkDumplicatedParameters(const QList<QPair<QString, IRequestImpl::FunType>>& maps, const IRequestImpl* ptr, const QString& name)
//{
//    static const QByteArray fakeVal = "&y&u$e$k#e#y*u*a@n@";
//    bool convertOk;
//    if(IConstantUtil::DebugMode){
//        int count = 0;
//        for(auto pair : maps){
//            std::mem_fn(pair.second)(ptr, name, convertOk);     // TODO:这里要检查一下
//            if(convertOk){
//                count ++;
//            }
//        }

//        if(count >1){
//            IAssertInfo info;
//            info.reason = name + " parameter exist more than one in (body, path, param, session, cookie), please check. name : " + name;
//            $Ast->fatal("checkDumplicatedParameters_find_More_than_one_value", info);
//        }
//    }
//}

//QString IRequestImplHelper::getOriginName(const QString& name, const QString& suffix)
//{
//    if(name.endsWith(suffix)){
//        return name.left(name.length() - suffix.length());
//    }
//    return name;
//}

$PackageWebCoreEnd
