#include "IRequestImpl.h"

#include <algorithm>
#include "IRequestAssert.h"
#include "core/application/IAsioApplication.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IHeaderUtil.h"
#include "core/base/ICodecUtil.h"
#include "core/base/IToeUtil.h"
#include "core/config/IProfileImport.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/invalid/IHttpRequestHeaderFieldTooLargeInvalid.h"
#include "http/jar/IHeaderJar.h"
#include "http/net/IRequest.h"
#include "http/net/server/ITcpConnection.h"
#include "http/net/IRequestManage.h"
#include "http/controller/IHttpManage.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IResponseImpl.h"
#include "http/net/server/IHttpRequestHandler.h"

$PackageWebCoreBegin

$UseAssert(IRequestAssert)

//namespace IRequestImplHelper{
//    void checkDumplicatedParameters(const QList<QPair<QString, IRequestImpl::FunType>>& maps, const IRequestImpl* ptr, const QString& name);
//    QString getOriginName(const QString& name, const QString& suffix);
//}

IRequestImpl::IRequestImpl(IRequest* self)
    : m_request(self), m_raw(new IRequestRaw(self)),
     m_connection(self->m_connection), m_data(self->m_connection->m_data)
{
}

IRequestImpl::~IRequestImpl()
{
    delete m_responseImpl;
    m_responseImpl = nullptr;

    delete m_raw;
    m_raw = nullptr;
}

QJsonValue IRequestImpl::requestJson(bool& ok) const
{
    return m_raw->getRequestJson(ok);
}

int IRequestImpl::contentLength() const
{
    return m_raw->m_requestHeaders.value(IHttpHeader::ContentLength).toQString().toInt();
}

IStringView IRequestImpl::contentType() const
{
    return m_raw->m_requestHeaders.value(IHttpHeader::ContentType);
}

/*
QByteArray IRequestImpl::getParameter(const QString &name, bool& ok) const
{
    // 这里独自处理
    if(name.endsWith("_content")){
        IRequestImpl::getContentParameter(name, ok);
    }

    const auto& map = parameterResolverMap();
    for(auto pair : map){
        if(name.endsWith(pair.first)){
            return std::mem_fn(pair.second)(this, name, ok);
        }
    }

    return getMixedParameter(name, ok);
}

QByteArray IRequestImpl::getMixedParameter(const QString &name, bool& ok) const
{
    static const QString mixedSuffix = "_mixed";
    const auto& map = parameterResolverMap();
    IRequestImplHelper::checkDumplicatedParameters(map, this, name);        //check
    const QString& originName = IRequestImplHelper::getOriginName(name, mixedSuffix);
    for(auto& pair : map){
        auto result = std::mem_fn(pair.second)(this, originName, ok);
        if(ok){
            return result;
        }
    }

    // 这里单独处理 content TODO: 这里可能会出现bug.
    auto result = IRequestImpl::getContentParameter(name, ok);
    if(ok){
        return result;
    }

    ok = false;
    return {};
}

// TODO: 这个感觉不对，看一下
QByteArray IRequestImpl::getContentParameter(const QString &name, bool& ok) const
{
    // FIXME:
    return {};

    //    Q_UNUSED(name);
//    if(m_raw->m_method != IHttpMethod::GET){
//        IToeUtil::setOk(ok, false);
//    }
//    IToeUtil::setOk(ok, true);
//    return m_raw->m_requestBody;
}`

QByteArray IRequestImpl::getUrlParameter(const QString &name, bool& ok) const
{
    // FIXME:
    return {};
    //    static const QString suffix = "_url";

//    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
//    if(m_raw->m_requestUrlParameters.contains(originName)){
//        ok = true;
//        return m_raw->m_requestUrlParameters[originName].toUtf8();
//    }

//    ok = false;
//    return {};
}

// TODO: 这里有一个 fatal, 需要处理掉
// TODO: 数据处理不完全
QByteArray IRequestImpl::getBodyParameter(const QString &name, bool& ok) const
{
    static const QString suffix = "_body";

    ok = true;
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    switch (m_raw->m_requestMime) {
    case IHttpMime::MULTIPART_FORM_DATA:
        return getMultiPartFormData(originName, ok);
    case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
        return getFormUrlValue(originName, ok).toUtf8();
    case IHttpMime::APPLICATION_JSON:
    case IHttpMime::APPLICATION_JSON_UTF8:
        return getJsonData(originName, ok);
    case IHttpMime::TEXT_XML:
        ok = false;
        $Ast->fatal("irequest_xml_currently_not_supported");
        break;
    case IHttpMime::TEXT_PLAIN:
    case IHttpMime::TEXT_PLAIN_UTF8:
        ok = false;
        return {};
    default:
        ok = false;
        return {};
    }

    ok = false;
    return {};
}

QByteArray IRequestImpl::getHeaderParameter(const QString &name, bool& ok) const
{
    static const QString suffix = "_header";
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    return m_raw->m_headerJar->getRequestHeaderValue(originName, ok).toUtf8();
}

QByteArray IRequestImpl::getParamParameter(const QString &name, bool& ok) const
{
    // FIXME:
    return {};
//    static QString suffix = "_param";

//    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
//    if(m_raw->m_requestPathParameters.contains(originName)){
//        ok = true;
//        return m_raw->m_requestPathParameters[originName].toUtf8();
//    }

//    ok = false;
//    return {};
}

// TODO: 这个地方的 cookie 需要查看原文档
QByteArray IRequestImpl::getCookieParameter(const QString &name, bool& ok) const
{
    // FIXME:
    return {};

//    static const QString suffix = "_cookie";
//    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

//    auto values = m_raw->m_requestCookieParameters.values(originName);
//    ok = values.length() == 1;
//    return values.length() > 0 ? values.first().toUtf8() : QByteArray();
}

// TODO: session not setted!!
QByteArray IRequestImpl::getSessionParameter(const QString &name, bool& ok) const
{
    static const QString suffix = "_session";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    Q_UNUSED(originName)

    qFatal("session current not supported");
    IToeUtil::setOk(ok, false);
    return {};
}


QString IRequestImpl::getFormUrlValue(const QString &name, bool& ok) const
{
    // FIXME:
    return {};
//    if(m_raw->m_requestBodyParameters.contains(name)){
//        ok = true;
//        return m_raw->m_requestBodyParameters[name];
//    }

//    ok = false;
//    return {};
}

QByteArray IRequestImpl::getMultiPartFormData(const QString &name, bool& ok) const
{
    // FIXME:
//    for(auto& part : m_raw->m_requestMultiParts){
//        if(part.name == name){
//            ok = true;
//            return part.content;
//        }
//    }

//    ok = false;
    return {};
}

QByteArray IRequestImpl::getJsonData(const QString &name, bool& ok) const
{
    auto json = requestJson(ok);
    if(!ok){
        return {};
    }

    auto value = IJsonUtil::getJsonValue(json, name, ok);
    if(!ok){
        return {};
    }

    switch (value.type()) {
    case QJsonValue::Type::Bool:
        return IConvertUtil::toByteArray(IConvertUtil::toString(value.toBool()));
    case QJsonValue::Type::Double:
        return IConvertUtil::toByteArray(IConvertUtil::toString(value.toDouble()));
    case QJsonValue::Type::Array:
    case QJsonValue::Type::Object:
        return IJsonUtil::toByteArray(value, ok);
    case QJsonValue::Type::String:
        return value.toString().toUtf8();
    case QJsonValue::Type::Null:
        ok = false;      // TODO: json 的null 值问题 json 有 null 值, 这个可能有转换方面的bug.
        return {};
    case QJsonValue::Type::Undefined:
        ok = false;
        return {};
    }
    ok = false;
    return {};
}

//QList<QPair<QString, IRequestImpl::FunType>> IRequestImpl::parameterResolverMap() const
//{
//    static const QList<QPair<QString, IRequestImpl::FunType>> map = {
//        {"_param",      &IRequestImpl::getParamParameter},
//        {"_body",       &IRequestImpl::getBodyParameter},
//        {"_url",        &IRequestImpl::getUrlParameter},
//        {"_header",     &IRequestImpl::getHeaderParameter},
////        {"_content",    &IRequestImpl::getContentParameter },     // 这里并不包含 _content, 因为解析时 _content 的解析和其他的解析冲突
//        {"_cookie",     &IRequestImpl::getCookieParameter},
//        //        {"_session",    &IRequestImpl::getSessionParameter},
//    };
//    return map;
//}

*/

void IRequestImpl::parseData()
{
    int line[2];
    while(true){
        switch (m_readState) {
        case State::FirstLineState:
            if(!m_data.getLine(line)){
                return m_connection->doRead();
            }
            firstLineState(IStringView(m_data.m_data + line[0], line[1]));
            break;
        case State::HeaderState:
            if(!m_data.getLine(line)){
                return m_connection->doRead();
            }
            headerState(IStringView(m_data.m_data + line[0], line[1]));
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

        if(!m_raw->isValid()){
            m_readState = State::EndState;
        }
    }
}

std::vector<asio::const_buffer> IRequestImpl::getResult()
{
    m_responseImpl = new IResponseImpl(m_raw);
    return m_responseImpl->getContent();
}

IStringView IRequestImpl::stash(QByteArray data)
{
    m_stash.emplace_back(std::move(data));
    return IStringView(m_stash.back().data(), m_stash.back().length());
}

void IRequestImpl::firstLineState(IStringView data)
{
    m_data.m_parsedSize += data.length();
    parseFirstLine(data.substr(0, data.length()-2));
    if(!m_raw->isValid()){
        return;
    }

    resolveFirstLine();
    resolvePathProcessor();

    m_readState = State::HeaderState;
}

void IRequestImpl::headerState(IStringView data)
{
    m_data.m_parsedSize += data.length();
    if(data.length() != 2){
        parseHeader(data.substr(0, data.length()-2));
        return;
    }

    resolveHeaders();

    if(m_contentLength || !m_multipartBoundary.empty()){
        m_readState = State::HeaderGapState;
    }else{
        m_readState = State::EndState;
    }
}

bool IRequestImpl::headerGapState()
{
    m_readState = BodyState;
    int readLength = m_data.m_readSize - m_data.m_parsedSize;
    if(m_contentLength){
        if(m_data.m_parsedSize + m_contentLength < m_data.m_maxSize){   // 表示可以使用 data 空间
            if(readLength == m_contentLength){
                return true;        // 表示可以直接解析
            }
            m_connection->doRead(); // 继续读取
        }else{
            m_bodyInData = false;   // 表示数据存放在 buffer 中
            auto data = asio::buffer_cast<char*>(m_data.m_buff.prepare(m_contentLength));
            memcpy(data, m_data.m_data + m_data.m_parsedSize, readLength); // 拷贝数据
            m_data.m_buff.commit(readLength);
            m_connection->doReadStreamBy(m_contentLength-readLength);
        }
    }else if(!m_multipartBoundary.empty()){
        IStringView view(m_data.m_data + m_data.m_parsedSize, readLength);
        if(view.find(m_multipartBoundaryEnd) != std::string_view::npos){
            return true;
        }

        m_bodyInData = false;
        auto data = asio::buffer_cast<char*>(m_data.m_buff.prepare(readLength * 2));
        memcpy(data, m_data.m_data + m_data.m_parsedSize, readLength); // 拷贝数据
        m_connection->doReadStreamBy(m_contentLength-readLength);
        m_data.m_buff.commit(readLength);
        m_connection->doReadStreamUntil(m_multipartBoundaryEnd);
    }
    return false;
}

void IRequestImpl::bodyState()
{
    if(m_contentLength){
        resolveBodyContent();
    }else if(!m_multipartBoundary.empty()){
        resolveMultipartContent();
    }

    if(m_request->isValid()){
        switch (m_raw->m_requestMime) {
        case IHttpMime::MULTIPART_FORM_DATA:
            parseMultiPartData(m_raw->m_requestBody);
            break;
        case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
            parseUrlEncodedData(m_raw->m_requestBody, true);
            break;
        case IHttpMime::APPLICATION_JSON:
        case IHttpMime::APPLICATION_JSON_UTF8:
            parseJsonData(m_raw->m_requestBody);
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
        IHttpRequestHandler::instance()->handle(*m_request);
    });
}

void IRequestImpl::parseFirstLine(IStringView line)
{
    static $UInt urlMaxLength("http.urlMaxLength");
    if(line.length() >= urlMaxLength){
         return m_raw->setInvalid(IHttpBadRequestInvalid("request url is too long"));
    }

    int pos = 0;
    // method
    auto index = line.find_first_of(' ', pos);
    if(index == std::string::npos){
        return m_raw->setInvalid(IHttpBadRequestInvalid("can not resolve current method type"));
    }
    auto method = line.substr(pos, index);
    m_raw->m_method = IHttpMethodUtil::toMethod(method);
    if(m_raw->m_method == IHttpMethod::UNKNOWN){
        return m_raw->setInvalid(IHttpBadRequestInvalid("can not resolve current method type"));
    }
    pos = index + 1;

    // path TODO: 检查一下url 是否合规
    index = line.find_first_of(' ', pos);
    if(index == std::string_view::npos){
        return m_raw->setInvalid(IHttpBadRequestInvalid("request path is not correct"));
    }
    m_raw->m_rawUrl = line.substr(pos, index-pos);
    pos = index +1;

    // version
    m_raw->m_httpVersion = IHttpVersionUtil::toVersion(line.substr(pos));
    if(m_raw->m_httpVersion == IHttpVersion::UNKNOWN){
        return m_raw->setInvalid(IHttpBadRequestInvalid("current version is not supported"));
    }
}

void IRequestImpl::resolveFirstLine()
{
    auto index = m_raw->m_rawUrl.find_first_of('?');
    if(index == std::string_view::npos){
        m_raw->m_rawPath = m_raw->m_rawUrl;
        m_raw->m_url = stash(QByteArray::fromPercentEncoding(QByteArray(m_raw->m_rawUrl.data(), m_raw->m_rawUrl.length())));
        return;
    }

    m_raw->m_rawPath = m_raw->m_rawUrl.substr(0, index);
    m_raw->m_url = QByteArray::fromPercentEncoding(QByteArray(m_raw->m_rawUrl.data(), m_raw->m_rawUrl.length()));

    m_raw->m_rawPathArgs = m_raw->m_rawUrl.substr(index+1);
    parseUrlEncodedData(m_raw->m_rawPathArgs, false);
}

void IRequestImpl::parseHeader(IStringView line)
{
    static $UInt headerMaxLength("http.headerMaxLength");
    auto index = line.find_first_of(':');
    if(index == std::string_view::npos){
        return m_raw->setInvalid(IHttpBadRequestInvalid("server do not support headers item multiline, or without key/value pair"));  // SEE: 默认不支持 headers 换行书写
    }

    if(line.length() > headerMaxLength){
        m_raw->setInvalid(IHttpRequestHeaderFieldTooLargeInvalid());
    }

    auto key = line.substr(0, index).trimmed();
    auto value = line.substr(index+1).trimmed();
    m_raw->m_requestHeaders.insertMulti(key, value);
}

void IRequestImpl::resolveHeaders()
{
    if(m_raw->m_requestHeaders.contains(IHttpHeader::ContentLength)){
        bool ok;
        m_contentLength = m_raw->m_requestHeaders.value(IHttpHeader::ContentLength).toQString().toUInt(&ok);
        if(!ok){
            return m_raw->setInvalid(IHttpBadRequestInvalid("ContentLength error"));
        }
        static $Int bodyMaxLength("http.bodyMaxLength");
        if(m_contentLength > bodyMaxLength){
            return m_raw->setInvalid(IHttpBadRequestInvalid("Content Length too large to accept"));
        }
    }

    auto contentType = m_raw->m_requestHeaders.value(IHttpHeader::ContentType);
    if(!contentType.empty()){
        m_raw->m_requestMime = IHttpMimeUtil::toMime(contentType);
        if(m_raw->m_requestMime == IHttpMime::MULTIPART_FORM_DATA){
            m_multipartBoundary = getBoundary(contentType);
            if(m_multipartBoundary.empty()){
                m_request->setInvalid(IHttpBadRequestInvalid("multipart request has no boundary"));
                return;
            }else{
                m_multipartBoundaryEnd = stash(m_multipartBoundary.toQByteArray() + "--");
            }
        }
    }

    resolveCookieHeaders();
}

void IRequestImpl::resolveCookieHeaders()
{
    auto cookies = m_raw->m_requestHeaders.values(IHttpHeader::Cookie);
    for(const auto& cookie : cookies){
        auto args = cookie.split('=');
        if(args.length() == 1){
            m_raw->m_requestCookieParameters.insertMulti(args.first(), args.first());
        }else{
            m_raw->m_requestCookieParameters.insertMulti(args.first(), args.last());
        }
    }
}

void IRequestImpl::resolvePathProcessor()
{
    if(m_raw->m_method == IHttpMethod::OPTIONS){
        m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Option;
        return;
    }

    static auto controllerManage = IHttpManage::instance();
    static const bool isUrlActionEnabled = controllerManage->isUrlActionNodeEnabled();     // process as dynamic server first
    if(isUrlActionEnabled){
        m_raw->m_processer.node = controllerManage->getUrlActionNode(*m_request);
        if(m_raw->m_processer.node != nullptr){
            m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Function;
            return;
        }
    }

    static bool isStaticFileEnabled = controllerManage->isStaticFileActionPathEnabled();        // process as static file server then
    if(isStaticFileEnabled && m_request->method() == IHttpMethod::GET){
        m_raw->m_processer.path = controllerManage->getStaticFileActionPath(*m_request);
        if(!m_raw->m_processer.path.isEmpty()){
            m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Path;
            return;
        }

        static $Bool handleDir{"http.fileService.folderHandled"};
        if(handleDir){
            m_raw->m_processer.entries = controllerManage->getStaticFolderActionPath(*m_request);
            if(!m_raw->m_processer.entries.isEmpty()){
                m_raw->m_processer.type = IRequestRaw::ProcessUnit::Type::Directory;
                return;
            }
        }
    }

    QString info = m_request->url().toQString() + " " + IHttpMethodUtil::toString(m_request->method()) + " has no function to handle";
    m_request->setInvalid(IHttpNotFoundInvalid(std::move(info)));
}

void IRequestImpl::resolveBodyContent()
{
    if(m_bodyInData){
        auto readSize = m_data.m_readSize - m_data.m_parsedSize;
        if(m_contentLength != readSize){
            return m_request->setInvalid(IHttpBadRequestInvalid("content-length mismatch"));
        }
        m_raw->m_requestBody = IStringView(m_data.m_data + m_data.m_parsedSize, readSize);
    }else{
        if(m_contentLength != m_data.m_buff.size()){
            return m_request->setInvalid(IHttpBadRequestInvalid("content-length mismatch"));
        }
        m_raw->m_requestBody = IStringView(asio::buffer_cast<const char*>(m_data.m_buff.data()), m_data.m_buff.size());
    }
}

void IRequestImpl::resolveMultipartContent()
{
    if(m_bodyInData){
        m_raw->m_requestBody = IStringView(m_data.m_data + m_data.m_parsedSize, m_data.m_readSize - m_data.m_parsedSize);
    }else{
        m_raw->m_requestBody = IStringView(asio::buffer_cast<const char*>(m_data.m_buff.data()), m_data.m_buff.size());
    }
    if(!m_raw->m_requestBody.endWith(m_multipartBoundaryEnd)){
        m_request->setInvalid(IHttpBadRequestInvalid("multipart data do not have end tag"));
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
            m_raw->setInvalid(IHttpBadRequestInvalid("the parameters in body should be pair"));
        }
        if(isBody){
            m_raw->m_requestBodyParameters[value.substr(0, partIndex).trimmed()] = value.substr(partIndex + 1).trimmed();
        }else{
            m_raw->m_requestPathParameters[value.substr(0, partIndex).trimmed()] = value.substr(partIndex + 1).trimmed();
        }
        pos = index+1;
    }
}

void IRequestImpl::parseJsonData(IStringView data)
{
    qDebug() << "start to parse json data" << data;
}

void IRequestImpl::parseMultiPartData(IStringView data)
{
    auto endPos = data.find(m_multipartBoundaryEnd);
    if(endPos == IStringView::npos){
        m_request->setInvalid(IHttpBadRequestInvalid("multipart end error"));
        return;
    }

    int pos{};
    auto indexFirst = data.find(m_multipartBoundary, pos);
    for(;;){
        auto indexSecond = data.find(m_multipartBoundary, indexFirst+ m_multipartBoundary.length());
        if(indexSecond == IStringView::npos){
            break;
        }
        auto content=data.substr(indexFirst + m_multipartBoundary.length(), indexSecond - m_multipartBoundary.length()).trimmed();
        qDebug() << content;
        m_raw->m_requestMultiParts.append(IMultiPart(content));
        indexFirst = indexSecond;
    }
}

IStringView IRequestImpl::getBoundary(IStringView data)
{
    static std::string prefix = "boundary=";
    auto index = data.find(prefix);
    if(index == std::string::npos){
        return {};
    }
    auto view = data.substr(index + prefix.length());
    return stash("--" + view.toQByteArray());
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
