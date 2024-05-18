#include "IRequestImpl.h"

#include "IRequestAssert.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IHeaderUtil.h"
#include "core/base/ICodecUtil.h"
#include "core/base/IToeUtil.h"
#include "core/config/IProfileImport.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/jar/IHeaderJar.h"
#include "http/net/IRequest.h"
#include "http/net/IRequestManage.h"
#include "http/net/impl/IReqRespRaw.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

$UseAssert(IRequestAssert)

namespace IRequestImplHelper{
    bool isPathValid(const QString& path);
    void checkDumplicatedParameters(const QList<QPair<QString, IRequestImpl::FunType>>& maps, const IRequestImpl* ptr, const QString& name);
    QString getOriginName(const QString& name, const QString& suffix);
}

IRequestImpl::IRequestImpl(IRequest* self, asio::ip::tcp::socket socket)
    : m_socket(std::move(socket))
{
    raw = new IReqRespRaw(self);
    doRead();
}

IRequestImpl::~IRequestImpl()
{
    delete raw;
    raw = nullptr;
}

QJsonValue IRequestImpl::requestJson(bool& ok) const
{
    return raw->getRequestJson(ok);
}

int IRequestImpl::contentLength() const
{
    return m_data.contentLength;
}

QString IRequestImpl::contentType() const
{
    return raw->m_requestHeaders.value(IHttpHeader::ContentType);
}

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
    Q_UNUSED(name);
    if(raw->m_method != IHttpMethod::GET){
        IToeUtil::setOk(ok, false);
    }
    IToeUtil::setOk(ok, true);
    return raw->m_requestBody;
}

QByteArray IRequestImpl::getUrlParameter(const QString &name, bool& ok) const
{
    static const QString suffix = "_url";

    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    if(raw->m_requestUrlParameters.contains(originName)){
        ok = true;
        return raw->m_requestUrlParameters[originName].toUtf8();
    }

    ok = false;
    return {};
}

// TODO: 这里有一个 fatal, 需要处理掉
// TODO: 数据处理不完全
QByteArray IRequestImpl::getBodyParameter(const QString &name, bool& ok) const
{
    static const QString suffix = "_body";

    ok = true;
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    switch (raw->m_requestMime) {
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

    return raw->m_headerJar->getRequestHeaderValue(originName, ok).toUtf8();
}

QByteArray IRequestImpl::getParamParameter(const QString &name, bool& ok) const
{
    static QString suffix = "_param";

    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    if(raw->m_requestParamParameters.contains(originName)){
        ok = true;
        return raw->m_requestParamParameters[originName].toUtf8();
    }

    ok = false;
    return {};
}

// TODO: 这个地方的 cookie 需要查看原文档
QByteArray IRequestImpl::getCookieParameter(const QString &name, bool& ok) const
{
    static const QString suffix = "_cookie";
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    QByteArray ret;
    const auto& cookies = raw->m_requestCookieParameters;
    int count{0};
    for(const auto& cookie : cookies){
        if(cookie.first == originName){
            if(count == 0){
                ret = cookie.second.toUtf8();
            }
            count ++;
        }
    }

    ok = count == 1;
    return ret;
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

void IRequestImpl::doRead()
{
    m_socket.async_read_some(m_data.getNextBuffer(), [&](std::error_code ec, int length){
        if(!ec){
            m_data.endPos += length;
            parseData();
        }else{
            qDebug() << "connection lost";
        }
    });
}

void IRequestImpl::doWrite()
{
    asio::async_write(m_socket, asio::buffer("hello world"), [&](std::error_code ec, int length){
        if(!ec){
            // check length;
            m_socket.close();
        }else{
            qDebug() << "connection write lost";
        }
    });
}

//void IRequestImpl::resolve()
//{
//    if(!resolvePeerInfo()){
//        return;
//    }

//    if(!resolveFirstLine()){
//        return;
//    }

//    if(!resolveHeaders()){
//        return;
//    }

//    if(!resolveCookies()){
//        return;
//    }

//    if(!resolveBody()){
//        return;
//    }
//}

QString IRequestImpl::getFormUrlValue(const QString &name, bool& ok) const
{
    if(raw->m_requestBodyParameters.contains(name)){
        ok = true;
        return raw->m_requestBodyParameters[name];
    }

    ok = false;
    return {};
}

QByteArray IRequestImpl::getMultiPartFormData(const QString &name, bool& ok) const
{
    for(auto& part : raw->m_requestMultiParts){
        if(part.name == name){
            ok = true;
            return part.content;
        }
    }

    ok = false;
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

QList<QPair<QString, IRequestImpl::FunType>> IRequestImpl::parameterResolverMap() const
{

    static const QList<QPair<QString, IRequestImpl::FunType>> map = {
        {"_param",      &IRequestImpl::getParamParameter},
        {"_body",       &IRequestImpl::getBodyParameter},
        {"_url",        &IRequestImpl::getUrlParameter},
        {"_header",     &IRequestImpl::getHeaderParameter},
//        {"_content",    &IRequestImpl::getContentParameter },     // 这里并不包含 _content, 因为解析时 _content 的解析和其他的解析冲突
        {"_cookie",     &IRequestImpl::getCookieParameter},
        //        {"_session",    &IRequestImpl::getSessionParameter},
    };
    return map;
}

void IRequestImpl::parseData()
{
    int line[2];    // 这个在之后可以考虑是 4 个字节，因为还有扩展部分的数据要传输
    static std::vector<void(IRequestImpl::*)(int[2])> stateFun = {
        &IRequestImpl::startState, &IRequestImpl::firstLineState, &IRequestImpl::headerState
    };
    while(true){
        switch (m_data.readState) {
        case State::End:
            return endState();
        case State::HeaderGap:
            if(!headerGapState()){
                return doRead(); // 等待下一次的数据。
            }
            break;
        default:
            if(!m_data.getLine(line)){
                return doRead();
            }
            std::mem_fn(stateFun[m_data.readState])(this, line);
            m_data.startPos += line[1];
        }

        if(!raw->valid()){
            m_data.readState = State::End;
        }
    }
}

void IRequestImpl::startState(int line[2])
{
    parseFirstLine(QString::fromLocal8Bit(m_data.data + line[0], line[1]-2));
    m_data.readState = State::FirstLine;

    if(raw->valid()){
        resolveFirstLine();
    }
}

void IRequestImpl::firstLineState(int line[2])
{
    if(line[1] != 2){
        parseHeader(QString::fromLocal8Bit(m_data.data + line[0], line[1] -2));
        m_data.readState = Header;
        return;
    }

    m_data.readState = State::End;
}

void IRequestImpl::headerState(int line[2])
{
    if(line[1] != 2){
        parseHeader(QString::fromLocal8Bit(m_data.data + line[0], line[1] -2));
        return;
    }

    if(raw->m_requestHeaders.contains(IHttpHeader::ContentLength)){
        m_data.contentLength = raw->m_requestHeaders.value(IHttpHeader::ContentLength).toInt();
        if(m_data.contentLength != 0){
            m_data.readState = State::HeaderGap;
            m_data.configBodyType(raw->m_requestHeaders.value(IHttpHeader::ContentType));
        }
    }else if(raw->m_requestHeaders.contains(IHttpHeader::ContentType) &&
             raw->m_requestHeaders.value(IHttpHeader::ContentType).startsWith("multipart/form-data;")){
        m_data.readState = State::HeaderGap;
        m_data.bodyType = BodyType::MultiPart;
    }else{
        m_data.readState = State::End;
    }

    resolveHeaders();       // 这个还可以再延后处理，万一其他数据出问题了呢
}

// return true 表示数据解析完成
// return false 表示数据还需要进一步的读取。
bool IRequestImpl::headerGapState()
{
    if(m_data.bodyType == BodyType::MultiPart){
        m_data.configBoundary(raw->m_requestHeaders.value(IHttpHeader::ContentType));
        return true;
    }
    if(m_data.contentLength != 0){
//        if(line[2] == m_data.bodyLength){
//            // 获得了数据，进行解析，
//        }
    }
    // 表示 headerGap 没有处理完成， 还需要进一步的处理数据
    return false;
}

void IRequestImpl::endState()
{

}

void IRequestImpl::parseFirstLine(QString line)
{
    static $Int urlMaxLength("http.urlMaxLength");
    if(line.length() >= urlMaxLength){
         return raw->setInvalid(IHttpBadRequestInvalid("request url is too long"));
    }

    QStringList content = line.split(' '); // NOTE: here should be optimized
    if(content.length() != 3){
        return raw->setInvalid(IHttpBadRequestInvalid("first line of request is not supported"));
    }

    raw->m_method = IHttpMethodUtil::toMethod(content[0]);
    if(raw->m_method == IHttpMethod::UNKNOWN){
        return raw->setInvalid(IHttpBadRequestInvalid("can not resolve current method type"));
    }

    raw->m_realUrl = QString(QByteArray::fromPercentEncoding(content[1].toUtf8()));
    if(!IRequestImplHelper::isPathValid(raw->m_realUrl)){
        return raw->setInvalid(IHttpBadRequestInvalid("request url is not correct. url:" + raw->m_realUrl));
    }

    raw->m_httpVersion = IHttpVersionUtil::toVersion(content[2]);
    if(raw->m_httpVersion == IHttpVersion::UNKNOWN){
        return raw->setInvalid(IHttpBadRequestInvalid("current version is not supported"));
    }
}

void IRequestImpl::resolveFirstLine()
{
    QStringList spices = raw->m_realUrl.split('?');
    raw->m_url = spices.first();
    if(spices.length() == 2){
        if(!resolveFirstLineArguments(spices[1], false)){
            return;
        }
    }
}

bool IRequestImpl::resolveFirstLineArguments(const QString &content, bool isBody)
{
    QStringList list = QString(QByteArray::fromPercentEncoding(content.toUtf8())).split('&');
    for(auto val : list){
        QStringList map = val.split('=');
        if(map.length() != 2){
            raw->setInvalid(IHttpBadRequestInvalid("the parameters in body should be pair"));
            return false;
        }

        QString key = map.first();
        auto value = map.last();
        if(isBody){
            raw->m_requestBodyParameters[key] = value;
        }else{
            raw->m_requestParamParameters[key] = value;
        }
    }
    return true;
}

void IRequestImpl::parseHeader(QString line)
{
    qDebug() << "Header" << line;
    static $Int headerMaxLength("http.headerMaxLength");
    auto index = line.indexOf(':');
    if(index == -1){
        return raw->setInvalid(IHttpBadRequestInvalid("server do not support headers item multiline"));  // SEE: 默认不支持 headers 换行书写
    }

    auto key = line.left(index);
    auto value = line.mid(index + 1).trimmed();
    raw->m_requestHeaders.insertMulti(key, value);       // TODO: check
}

void IRequestImpl::resolveHeaders()
{
    static const QByteArray splitString = "; ";

    if(raw->m_headerJar->containRequestHeaderKey(IHttpHeader::Cookie)){
        bool ok;
        const QString rawCookie = raw->m_headerJar->getRequestHeaderValue(IHttpHeader::Cookie, ok);
        // TODO: 检查 ok 的值
        QString key, value;
        int index;
        auto parts = rawCookie.split(splitString);
        for(const auto& part : parts){
            key.clear();
            value.clear();
            index = part.indexOf('=');
            if(index<=0){       // 保证只有 key 的情形
                key = part;
            }else{
                key = part.mid(0, index);
                value = part.mid(index + 1);
            }
            raw->m_requestCookieParameters.append({key, value});
        }
    }
//    return true;

}

/*
bool IRequestImpl::resolvePeerInfo()
{
//    raw->peerName = raw->m_socket->peerName();
//    raw->peerPort = raw->m_socket->peerPort();
//    raw->peerAddress = raw->m_socket->peerAddress();
    return true;
}

bool IRequestImpl::resolveFirstLine()
{
    static $Int urlMaxLength("http.urlMaxLength");

    if(!raw->canSocketReadLine()){
        raw->setInvalid(IHttpBadRequestInvalid("can't read from socket"));
        return false;
    }
    auto line = raw->readSocketLine(urlMaxLength);

    if(line.length() == 0){
        raw->setInvalid(IHttpBadRequestInvalid("can't read from socket"));
        return false;
    }

    if(line.length() >= urlMaxLength){
         raw->setInvalid(IHttpBadRequestInvalid("request url is too long"));
         return false;
    }

    auto content = line.replace("\r\n", "").split(' '); // NOTE: here should be optimized
    if(content.length() != 3){
        raw->setInvalid(IHttpBadRequestInvalid("first line of request is not supported"));
        return false;
    }

    // TODO:
    raw->m_method = IHttpMethodUtil::toMethod(content[0]);
    if(raw->m_method == IHttpMethod::UNKNOWN){
//        raw->setInvalid(IHttpStatusCode::METHOD_NOT_ALLOWED_405, "can not resolve current method type");
        raw->setInvalid(IHttpBadRequestInvalid("can not resolve current method type"));

        return false;
    }

    // TODO:
    raw->m_httpVersion = IHttpVersionUtil::toVersion(content[2]);
    if(raw->m_httpVersion == IHttpVersion::UNKNOWN){
//        raw->setInvalid(IHttpStatusCode::HTTP_VERSION_NOT_SUPPORTED, "current version is not supported");
        raw->setInvalid(IHttpBadRequestInvalid("current version is not supported"));

        return false;
    }

    auto realUrl = QString(QByteArray::fromPercentEncoding(content[1]));
    if(!IRequestImplHelper::isPathValid(realUrl)){
        raw->setInvalid(IHttpBadRequestInvalid("request url is not correct. url:" + realUrl));
        return false;
    }

    auto spices = realUrl.split('?');
    raw->m_url = spices.first();
    if(spices.length() == 2){
        if(!resolveEncodeArguments(spices[1].toUtf8(), false)){
            return false;
        }
    }

    return true;
}

bool IRequestImpl::resolveHeaders()
{
    static $Int headerMaxLength("http.headerMaxLength");

    int totalCount = 0;
    QByteArray content;
    while((content = raw->readSocketLine()) != "\r\n"){

        totalCount += content.length();
        if(totalCount > headerMaxLength){  // check header length;
            raw->setInvalid(IHttpBadRequestInvalid("request of headers too large"));
            return false;
        }

        auto index = content.indexOf(':');
        if(index == -1){
            raw->setInvalid(IHttpBadRequestInvalid("server do not support headers item multiline"));  // SEE: 默认不支持 headers 换行书写
            return false;
        }

        auto key = content.left(index);
        auto value = content.mid(index + 1).replace("\r\n", "").trimmed();  // NOTE: here should be optimized
        raw->m_requestHeaders.append({key, value});
    }
    raw->m_requestMime = IHttpMimeUtil::toMime(contentType());

    return true;
}

// NOTE: this kind of resolve is not safe in keep-alive mode.
// TODO: whether GET method can reslove multipart data?
bool IRequestImpl::resolveBody()
{
    static $Int bodyMaxLength("http.bodyMaxLength");

    if(raw->m_method == IHttpMethod::GET) { // when get, do not resolve.
        return true;
    }

    auto length = contentLength();
    if(length == 0){
        return true;
    }

    if(length > bodyMaxLength){
        raw->setInvalid(IHttpBadRequestInvalid("the request body is too large"));
        return false;
    }

    raw->m_requestBody = raw->readSocket(length);
    if(raw->m_requestBody.length() != length){
        raw->setInvalid(IHttpBadRequestInvalid("the request body`s length is not equal to length provided by Content-Length header"));
        return false;
    }

    return resolveBodyContent();
}

// TODO: 在接收数据的时候，这里其实应该判断一下body 所用的编码方式，因为可能因为编码方式的错误导致内容出错
bool IRequestImpl::resolveBodyContent()
{
    if(raw->m_requestBody.length() == 0){
        return true;
    }

    switch (raw->m_requestMime) {
    case IHttpMime::MULTIPART_FORM_DATA:
        return resolveMultipartFormData();
    case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
        return resolveFormUrlEncoded();
    default:
        break; // 只解析上面两个，其他的不解析。 json and xml will be resolved when using it.
    }
    return true;
}

bool IRequestImpl::resolveMultipartFormData()
{
    auto boundaries = getBoundaries();
    for(auto i=0; i<boundaries.length()-1; i++){
        auto start = boundaries[i].second;
        auto end = boundaries[i+1].first;
        auto splitPos = raw->m_requestBody.indexOf("\r\n\r\n", start);  // here point to \r

        IMultiPart part;                                        // @optimized it!
        processMultiPartHeaders(part, start, splitPos + 2);     // from start to \r\n
        processMultiPartBody(part, splitPos + 4, end - 2);      // from bodyBegin to bodyEnd
        raw->m_requestMultiParts.append(part);
    }
    return resolveTrailer();
}

bool IRequestImpl::resolveTrailer()
{
    // TODO: this will be fixed in next version
    return true;
}

bool IRequestImpl::resolveFormUrlEncoded()
{
    return resolveEncodeArguments(raw->m_requestBody, true);
}



void IRequestImpl::processMultiPartHeaders(IMultiPart &part, int start, int end)
{
    auto posBegin = start;
    auto posEnd = raw->m_requestBody.indexOf("\r\n", posBegin);
    while(posEnd != -1 && posEnd < end){
        auto line = raw->m_requestBody.mid(posBegin, posEnd - posBegin);
        auto args = line.split(':');
//        auto key = QString(QByteArray::fromPercentEncoding(args.first()));
//        auto value = QString(QByteArray::fromPercentEncoding(args.last())).trimmed();
//        part.headers[key] = value;
        part.headers[ICodecUtil::urlDecode(args.first()).trimmed()] = ICodecUtil::urlDecode(args.last()).trimmed();
        posBegin = posEnd + 2;
        posEnd = raw->m_requestBody.indexOf("\r\n", posBegin);
    }
    part.resolveHeaders();
}

void IRequestImpl::processMultiPartBody(IMultiPart &part, int start, int end)
{
    if(part.mime != IHttpMime::MULTIPART_FORM_DATA){
        part.content = raw->m_requestBody.mid(start, end - start);
    } else {
        qFatal("error, please process");        // TODO: 这里不知道是否会有嵌套出现，默认没有，如果真的有了，再处理吧，我要睡觉了。
        qDebug() << "you should process this file again";
    }
}

QList<QPair<int, int> > IRequestImpl::getBoundaries()
{
    QList<QPair<int, int>> ret;
    auto boundary = getBoundaryParam(contentType());
    auto boundaryLength = boundary.length();
    if(boundary.isEmpty()){
        raw->setInvalid(IHttpBadRequestInvalid("multi part request boundary not set"));
        return ret;
    }
    auto endBoundary = boundary + "--\r\n";

    int pos = 0;
    auto index = raw->m_requestBody.indexOf(boundary, pos);
    while(index != -1){
        auto endPoint = index + boundaryLength;
        if(raw->m_requestBody[endPoint] == '\r' && raw->m_requestBody[endPoint + 1]== '\n'){
            pos = endPoint +1;
            QPair<int, int> boundaryPair{index, pos};
            ret.append(boundaryPair);
        }else if(raw->m_requestBody.mid(endPoint, 4) == "--\r\n"){
            pos = endPoint + 3;
            QPair<int, int> boundaryPair{index, pos};
            ret.append(boundaryPair);
            break;
        }else{
            raw->setInvalid(IHttpBadRequestInvalid("multi part request boundary error"));
            return ret;
        }
        index = raw->m_requestBody.indexOf(boundary, pos);
    }
    return ret;
}


*/


// TODO: 这里不对， 有路径没有被判断通过，
bool IRequestImplHelper::isPathValid(const QString& path){
    static QRegularExpression exp(R"(([\/\w \.-]*)*\/?$)");
    if(!exp.isValid()){
        qDebug() << "invalid" << exp.errorString();
    }

    return exp.match(path).hasMatch();
}

void IRequestImplHelper::checkDumplicatedParameters(const QList<QPair<QString, IRequestImpl::FunType>>& maps, const IRequestImpl* ptr, const QString& name)
{
    static const QByteArray fakeVal = "&y&u$e$k#e#y*u*a@n@";

    bool convertOk;
    if(IConstantUtil::DebugMode){
        int count = 0;
        for(auto pair : maps){
            std::mem_fn(pair.second)(ptr, name, convertOk);     // TODO:这里要检查一下
            if(convertOk){
                count ++;
            }
        }

        if(count >1){
            IAssertInfo info;
            info.reason = name + " parameter exist more than one in (body, path, param, session, cookie), please check. name : " + name;
            $Ast->fatal("checkDumplicatedParameters_find_More_than_one_value", info);
        }
    }
}

QString IRequestImplHelper::getOriginName(const QString& name, const QString& suffix){
    if(name.endsWith(suffix)){
        return name.left(name.length() - suffix.length());
    }
    return name;
}

bool IRequestImpl::Data::getLine(int* value)
{
    value[0] = startPos;
    for(int i=startPos; i<endPos-1; i++){
        if(data[i] == '\r' && data[i + 1] == '\n'){     // 这个可以通过 转换类型并 异或 完成数据的判断，更简单一点
            value[1] = i + 2 - startPos;
            return true;
        }
    }
    value[1] = startPos;
    return false;
}

void IRequestImpl::Data::configBodyType(const QString &data)
{
    bodyType =  BodyType::BinData;
}

void IRequestImpl::Data::configBoundary(const QString &mime)
{
    QRegularExpression expression("boundary=[\"]?(.+)[\"]?$");
    auto result = expression.match(mime);
    if(result.hasMatch()){
        auto boundary = result.captured(1);
        if(!boundary.startsWith("--")){
            boundary.prepend("--");
        }
        multipartBoundary = boundary;
    }
}


$PackageWebCoreEnd
