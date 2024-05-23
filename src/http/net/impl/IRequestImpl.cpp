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
#include "http/net/server/ITcpConnection.h"
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

IRequestImpl::IRequestImpl(IRequest* self)
    : m_request(self), raw(new IReqRespRaw(self))
{
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
    return raw->m_requestHeaders.value(IHttpHeader::ContentLength).toInt();
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

    auto values = raw->m_requestCookieParameters.values(originName);
    ok = values.length() == 1;
    return values.length() > 0 ? values.first().toUtf8() : QByteArray();
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

//void IRequestImpl::doRead()
//{
//    m_socket.async_read_some(m_data.getNextBuffer(), [&](std::error_code ec, int length){
//        if(!ec){
//            m_data.endPos += length;
//            parseData();
//        }else{
//            qDebug() << "connection lost";
//        }
//    });
//}

//void IRequestImpl::doWrite()
//{
//    asio::async_write(m_socket, asio::buffer("hello world"), [&](std::error_code ec, int length){
//        Q_UNUSED(length)
//        if(!ec){
//            // check length;
//            m_socket.close();
//        }else{
//            qDebug() << "connection write lost";
//        }
//    });
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
        switch (m_readState) {
        case State::End:
            return endState();
        case State::HeaderGap:
            if(!headerGapState()){
                return m_request->m_connection->doRead(); // 等待下一次的数据。
            }
            break;
        default:
            if(!m_request->m_connection->m_data.getLine(line)){
                return m_request->m_connection->doRead();
            }
            std::mem_fn(stateFun[m_readState])(this, line);
            m_request->m_connection->m_data.parsedSize += line[1];
        }

        if(!raw->valid()){
            m_readState = State::End;
        }
    }
}

void IRequestImpl::startState(int line[2])
{
    parseFirstLine(QString::fromLocal8Bit(m_request->m_connection->m_data.m_data + line[0], line[1]-2));
    m_readState = State::FirstLine;

    if(raw->valid()){
        resolveFirstLine();
    }
}

void IRequestImpl::firstLineState(int line[2])
{
    if(line[1] != 2){
        parseHeader(QString::fromLocal8Bit(m_request->m_connection->m_data.m_data + line[0], line[1] -2));
        m_readState = Header;
        return;
    }

    m_readState = State::End;
}

void IRequestImpl::headerState(int line[2])
{
    const auto &data = m_request->m_connection->m_data;

    if(line[1] != 2){
        parseHeader(QString::fromLocal8Bit(m_request->m_connection->m_data.m_data + line[0], line[1] -2));
        return;
    }

    // next state
    if(raw->m_requestHeaders.contains(IHttpHeader::ContentLength)){
        m_contentLength = raw->m_requestHeaders.value(IHttpHeader::ContentLength).toInt();
        if(m_contentLength != 0){
            m_readState = State::HeaderGap;
        }
    }else if(raw->m_requestHeaders.contains(IHttpHeader::ContentType) &&
             raw->m_requestHeaders.value(IHttpHeader::ContentType).startsWith("multipart/form-data;")){
        m_readState = State::HeaderGap;
    }else{
        m_readState = State::End;
    }

    resolveHeaders();
}

bool IRequestImpl::headerGapState()
{
    auto data = m_request->m_connection->m_data;
    if(raw->m_requestMime == IHttpMime::MULTIPART_FORM_DATA){
        m_multipartBoundary = getBoundary(raw->m_requestHeaders.value(IHttpHeader::ContentType));
        if(m_multipartBoundary.isEmpty()){
            m_request->setInvalid(IHttpBadRequestInvalid("multipart request has no boundary"));
            return false;
        }
        parseMultiPartBody();
        return true;
    }

    if(m_contentLength != 0){
        auto fileLength = data.readSize - data.parsedSize;
        if(fileLength >= m_contentLength){
            // 表示数据已经接收完成，可以进行处理了
            // 这里需要复制一下么 ?
            parseCommonBody();
            return true;
        }
    }
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
        if(!resolveFormedData(spices[1], false)){
            return;
        }
    }
}

void IRequestImpl::parseHeader(QString line)
{
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
    resolveCookieHeaders();
    raw->m_requestMime = IHttpMimeUtil::toMime(raw->m_requestHeaders.value(IHttpHeader::ContentType));
}

// TODO: 检查字符转义的问题
void IRequestImpl::resolveCookieHeaders()
{
    auto cookies = raw->m_requestHeaders.values(IHttpHeader::Cookie);
    for(const QString& cookie : cookies){
        auto parts = cookie.split("; ");
        for(const QString& part : parts){
            QStringList args = part.split("=");
            if(args.length() == 1){
                raw->m_requestCookieParameters.insertMulti(args.first(), args.first());
            }else{
                raw->m_requestCookieParameters.insertMulti(args.first(), args.last());
            }
        }
    }
}

void IRequestImpl::parseMultiPartBody()
{

}


bool IRequestImpl::resolveFormedData(const QString &content, bool isBody)
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

void IRequestImpl::parseCommonBody()
{
    const auto& data = m_request->m_connection->m_data;
    switch (raw->m_requestMime) {
    case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
    {
        QString body = QString::fromLocal8Bit
                (data.m_data + m_request->m_connection->m_data.parsedSize, data.readSize - data.parsedSize);
        resolveFormedData(body, true);
    }
        break;
//        return resolveFormUrlEncoded();
    default:
        break; // 只解析上面两个，其他的不解析。 json and xml will be resolved when using it.
    }
}

QString IRequestImpl::getBoundary(const QString &mime)
{
    QRegularExpression expression("boundary=[\"]?(.+)[\"]?$");
    auto result = expression.match(mime);
    if(result.hasMatch()){
        auto boundary = result.captured(1);
        if(!boundary.startsWith("--")){
            boundary.prepend("--");
        }
        return boundary;
    }
    return {};
}

/*


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

QString IRequestImplHelper::getOriginName(const QString& name, const QString& suffix)
{
    if(name.endsWith(suffix)){
        return name.left(name.length() - suffix.length());
    }
    return name;
}

//bool IRequestImpl::Data::getLine(int* value)
//{
//    value[0] = startPos;
//    for(int i=startPos; i<endPos-1; i++){
//        if(data[i] == '\r' && data[i + 1] == '\n'){     // 这个可以通过 转换类型并 异或 完成数据的判断，更简单一点
//            value[1] = i + 2 - startPos;
//            return true;
//        }
//    }
//    value[1] = startPos;
//    return false;
//}

//void IRequestImpl::Data::configBoundary(const QString &mime)
//{
//    QRegularExpression expression("boundary=[\"]?(.+)[\"]?$");
//    auto result = expression.match(mime);
//    if(result.hasMatch()){
//        auto boundary = result.captured(1);
//        if(!boundary.startsWith("--")){
//            boundary.prepend("--");
//        }
//        multipartBoundary = boundary;
//    }
//}


$PackageWebCoreEnd
