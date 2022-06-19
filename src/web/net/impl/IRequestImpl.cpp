#include "IRequestImpl.h"

#include "IRequestAst.h"
#include "base/IConstantUtil.h"
#include "base/IHeaderUtil.h"
#include "base/ICodecUtil.h"
#include "base/IToeUtil.h"
#include "web/net/IRequest.h"
#include "web/net/impl/IReqRespRaw.h"
#include "core/configuration/IConfigurationManage.h"

$PackageWebCoreBegin

$UseAsset(IRequestAst)

namespace IRequestImplHelper{
    bool isPathValid(const QString& path);
    void checkDumplicatedParameters(const QList<QPair<QString, IRequestImpl::FunType>>& maps, const IRequestImpl* ptr, const QString& name);
    QString getOriginName(const QString& name, const QString& suffix);
}

IRequestImpl::IRequestImpl(IReqRespRaw *raw)
{
    this->raw = raw;
}

QJsonValue &IRequestImpl::requestJson(bool *ok) const
{
    return raw->getRequestJson(ok);
}

QDomNode &IRequestImpl::requestXml(bool *ok) const
{
    return raw->getRequestXml(ok);
}

int IRequestImpl::contentLength() const
{
    bool convertOk;
    auto len = getHeaderParameter(IHttpHeader::ContentLength, &convertOk);
    if(!convertOk){
        return 0;
    }

    auto size = IConvertUtil::toInt(len, &convertOk);
    return convertOk ? size : 0;
}

QString IRequestImpl::contentType() const
{
    bool convertOk;
    auto value = getHeaderParameter(IHttpHeader::ContentType, &convertOk);
    if(!convertOk){
        return "";
    }
    return value;
}

QByteArray IRequestImpl::getParameter(const QString &name, bool* ok) const
{
    // 这里独自处理
    if(name.endsWith("_content")){
        IRequestImpl::getContentParameter(name, ok);
    }

    IToeUtil::setOk(ok, true);
    const auto& map = parameterResolverMap();
    for(auto pair : map){
        if(name.endsWith(pair.first)){
            return std::mem_fn(pair.second)(this, name, ok);
        }
    }

    return getMixedParameter(name, ok);
}

QByteArray IRequestImpl::getMixedParameter(const QString &name, bool* ok) const
{
    static const QString mixedSuffix = "_mixed";

    IToeUtil::setOk(ok, true);
    const auto& map = parameterResolverMap();

    IRequestImplHelper::checkDumplicatedParameters(map, this, name);        //check

    const QString& originName = IRequestImplHelper::getOriginName(name, mixedSuffix);

    for(auto& pair : map){
        auto result = std::mem_fn(pair.second)(this, originName, ok);
        if(*ok){
            return result;
        }
    }

    // 这里单独处理 content TODO: 这里可能会出现bug.
    auto result = IRequestImpl::getContentParameter(name, ok);
    if(*ok){
        return result;
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getContentParameter(const QString &name, bool *ok) const
{
    Q_UNUSED(name);
    IToeUtil::setOk(ok, true);
    if(raw->m_method != IHttpMethod::GET){
        IToeUtil::setOk(ok, false);
    }
    IToeUtil::setOk(ok, true);
    return raw->m_requestBody;
}

QByteArray IRequestImpl::getUrlParameter(const QString &name, bool* ok) const
{
    static const QString suffix = "_url";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    if(raw->m_requestUrlParameters.contains(originName)){
        return raw->m_requestUrlParameters[originName];
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getBodyParameter(const QString &name, bool*ok) const
{
    static const QString suffix = "_body";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    switch (raw->m_requestMime) {
    case IHttpMime::MULTIPART_FORM_DATA:
        return getMultiPartFormData(originName, ok);
    case IHttpMime::APPLICATION_WWW_FORM_URLENCODED:
        return getFormUrlValue(originName, ok);
    case IHttpMime::APPLICATION_JSON:
    case IHttpMime::APPLICATION_JSON_UTF8:
        return getJsonData(originName, ok);
    case IHttpMime::TEXT_XML:
        IToeUtil::setOk(ok, false);
        $Ast->fatal("irequest_xml_currently_not_supported");
        break;
    case IHttpMime::TEXT_PLAIN:
    case IHttpMime::TEXT_PLAIN_UTF8:
        IToeUtil::setOk(ok, false);
        return {};
    default:
        IToeUtil::setOk(ok, false);
        return {};
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getHeaderParameter(const QString &name, bool* ok) const
{
    static const QString suffix = "_header";
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    return raw->m_headerJar.getRequestHeaderValue(originName, ok).toUtf8();
}

QByteArray IRequestImpl::getParamParameter(const QString &name, bool* ok) const
{
    static QString suffix = "_param";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);
    if(raw->m_requestParamParameters.contains(originName)){
        return raw->m_requestParamParameters[originName];
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getCookieParameter(const QString &name, bool* ok) const
{
    static const QString suffix = "_cookie";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    Q_UNUSED(originName)

    qFatal("cookie current not supported");
    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getSessionParameter(const QString &name, bool* ok) const
{
    static const QString suffix = "_session";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    Q_UNUSED(originName)

    qFatal("session current not supported");
    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getAppParameter(const QString &name, bool* ok) const
{
    static const QString suffix = "_app";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    bool convertOk;
    auto value = IConfigurationManage::getApplicationValue(originName, &convertOk);
    if(convertOk){
        return IConvertUtil::toByteArray(value);
    }

    IToeUtil::setOk(ok, convertOk);
    return {};
}

QByteArray IRequestImpl::getSystemParameter(const QString &name, bool* ok) const
{
    static const QString suffix = "_system";

    IToeUtil::setOk(ok, true);
    const QString& originName = IRequestImplHelper::getOriginName(name, suffix);

    bool convertOk;
    auto value = IConfigurationManage::getSystemValue(originName, &convertOk);
    if(convertOk){
        return IConvertUtil::toByteArray(value);
    }

    IToeUtil::setOk(ok, convertOk);
    return {};
}

void IRequestImpl::resolve()
{
    if(!resolvePeerInfo()){
        return;
    }

    if(!resolveFirstLine()){
        return;
    }

    if(!resolveHeaders()){
        return;
    }

    if(!resolveCookies()){
        return;
    }

    if(!resolveBody()){
        return;
    }
}

QByteArray IRequestImpl::getFormUrlValue(const QString &name, bool* ok) const
{
    IToeUtil::setOk(ok, true);
    if(raw->m_requestBodyParameters.contains(name)){
        return raw->m_requestBodyParameters[name];
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getMultiPartFormData(const QString &name, bool*ok) const
{
    IToeUtil::setOk(ok, true);
    for(auto& part : raw->m_requestMultiParts){
        if(part.name == name){
            return part.content;
        }
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QByteArray IRequestImpl::getJsonData(const QString &name, bool* ok) const
{
    IToeUtil::setOk(ok, true);

    bool convertOk;
    auto json = requestJson(&convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    if(!convertOk){
        return {};
    }

    auto value = IJsonUtil::getJsonValue(json, name, &convertOk);
    IToeUtil::setOkAnd(ok, convertOk);
    if(!convertOk){
        return {};
    }

    switch (value.type()) {
    case QJsonValue::Type::Bool:
        return IConvertUtil::toByteArray(IConvertUtil::toString(value.toBool()));
    case QJsonValue::Type::Double:
        return IConvertUtil::toByteArray(IConvertUtil::toString(value.toDouble()));
    case QJsonValue::Type::Array:
    case QJsonValue::Type::Object:
        return IJsonUtil::toByteArray(value);
    case QJsonValue::Type::String:
        return value.toString().toUtf8();
    case QJsonValue::Type::Null:
        IToeUtil::setOk(ok, false);       // TODO: json 的null 值问题 json 有 null 值, 这个可能有转换方面的bug.
        return {};
    case QJsonValue::Type::Undefined:
        IToeUtil::setOk(ok, false);
        return {};
    }
    IToeUtil::setOk(ok, false);
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
        //        {"_cookie",     &IRequestImpl::getCookieParameter},
        //        {"_session",    &IRequestImpl::getSessionParameter},
        {"_app",        &IRequestImpl::getAppParameter},
        {"_system",     &IRequestImpl::getSystemParameter}
    };
    return map;
}

bool IRequestImpl::resolvePeerInfo()
{
    raw->peerName = raw->m_socket->peerName();
    raw->peerPort = raw->m_socket->peerPort();
    raw->peerAddress = raw->m_socket->peerAddress();
    return true;
}

bool IRequestImpl::resolveFirstLine()
{
    if(!raw->m_socket->canReadLine()){
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "can't read from socket");
        return false;
    }

    auto line = raw->m_socket->readLine(IConstantUtil::Request_Url_Max_Length);
    if(line.length() == 0){
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "can't read from socket");
        return false;
    }
    if(line.length() >=IConstantUtil::Request_Url_Max_Length){
         raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "request url is too long");
         return false;
    }

    auto content = line.replace("\r\n", "").split(' '); // NOTE: here should be optimized
    if(content.length() != 3){
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "first line of request is not supported");
        return false;
    }

    raw->m_method = IHttpMethodHelper::toMethod(content[0]);
    if(raw->m_method == IHttpMethod::UNKNOWN){
        raw->setInvalid(IHttpStatus::METHOD_NOT_ALLOWED_405, "can not resolve current method type");
        return false;
    }

    raw->m_httpVersion = IHttpVersionHelper::toVersion(content[2]);
    if(raw->m_httpVersion == IHttpVersion::UNKNOWN){
        raw->setInvalid(IHttpStatus::HTTP_VERSION_NOT_SUPPORTED, "current version is not supported");
        return false;
    }

    auto realUrl = QString(QByteArray::fromPercentEncoding(content[1]));
    if(!IRequestImplHelper::isPathValid(realUrl)){
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "request url is not correct. url:" + realUrl);
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
    int totalCount = 0;

    QByteArray content;
    while((content = raw->m_socket->readLine()) != "\r\n"){

        totalCount += content.length();
        if(totalCount > IConstantUtil::Request_Header_Max_Length){  // check header length;
            raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "request of headers too large");
            return false;
        }

        auto index = content.indexOf(':');
        if(index == -1){
            raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "server do not support headers item multiline");  // SEE: 默认不支持 headers 换行书写
            return false;
        }

        auto key = content.left(index);
        auto value = content.mid(index + 1).replace("\r\n", "").trimmed();  // NOTE: here should be optimized
        raw->m_requestHeaders.append({key, value});
    }
    raw->m_requestMime = IHttpMimeHelper::toMime(contentType());

    return true;
}

// TODO: 这里有一个问题,就是 cookie 编码的问题，网络上是建议 cookie encode, 并且使用 base64 编码。
// 这里为了方面使用，编码问题放在 middleWare 中进行，并且能够配置,这样，用户能够自我实现。
bool IRequestImpl::resolveCookies()
{
    static const QByteArray splitString = "; ";


    if(IConstantUtil::ICookiePluginEnabled && raw->m_headerJar.containRequestHeaderKey(IHttpHeader::Cookie)){
        const QString rawCookie = raw->m_headerJar.getRequestHeaderValue(IHttpHeader::Cookie, nullptr);

        QString key, value;
        auto parts = rawCookie.split(splitString);
        for(const auto& part : parts){
            key.clear();
            value.clear();
            auto index = part.indexOf('=');
            if(index<=0){       // 保证只有 key 的情形
                auto key = part;
            }else{
                auto key = part.mid(0, index);
                auto value = part.mid(index + 1);
            }
            raw->m_requestCookieParameters.append({key, value});
        }
    }
    return true;
}

// NOTE: this kind of resolve is not safe in keep-alive mode.
bool IRequestImpl::resolveBody()
{
    if(raw->m_method == IHttpMethod::GET) { // when get, do not resolve.
        return true;
    }

    auto length = contentLength();
    if(length == 0){
        return true;
    }

    if(length > IConstantUtil::Request_Body_Max_Length){
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "the request body is too large");
        return false;
    }

    raw->m_requestBody = raw->m_socket->read(length);
    if(raw->m_requestBody.length() != length){
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "the request body`s length is not equal to length provided by Content-Length header");
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

bool IRequestImpl::resolveEncodeArguments(const QByteArray &content, bool isBody)
{
    auto list = content.split('&');
    for(auto val : list){
        auto map = val.split('=');
        if(map.length() != 2){
            raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "the parameters in body should be pair");
            return false;
        }

        QString key = QString(QByteArray::fromPercentEncoding(map.first()));
        auto value = QByteArray::fromPercentEncoding(map.last());
        if(isBody){
            raw->m_requestBodyParameters[key] = value;
        }else{
            raw->m_requestParamParameters[key] = value;
        }
    }
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
        raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "multi part request boundary not set");
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
            raw->setInvalid(IHttpStatus::BAD_REQUEST_400, "multi part request boundary error");
            return ret;
        }
        index = raw->m_requestBody.indexOf(boundary, pos);
    }
    return ret;
}

QByteArray IRequestImpl::getBoundaryParam(const QString &mime)
{
    QRegularExpression expression("boundary=[\"]?(.+)[\"]?$");
    auto result = expression.match(mime);
    if(!result.hasMatch()){
        return "";
    }
    auto boundary = result.captured(1);
    if(!boundary.startsWith("--")){
        boundary.prepend("--");
    }
    return boundary.toUtf8();
}

bool IRequestImplHelper::isPathValid(const QString& path){
    static QRegularExpression exp(R"(^(((file|gopher|news|nntp|telnet|http|ftp|https|ftps|sftp)://)?|(www\.))+(([a-zA-Z0-9\._-]+\.[a-zA-Z]{2,6}(:[0-9]{1,6})?)|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})(:[0-9]{1,6})?)?(/[a-zA-Z0-9\&%_\./-~-]*)?$)");
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
            std::mem_fn(pair.second)(ptr, name, &convertOk);
            if(convertOk){
                count ++;
            }
        }

        if(count >1){
            IAssetInfo info;
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


$PackageWebCoreEnd
