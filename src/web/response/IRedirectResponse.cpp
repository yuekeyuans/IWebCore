#include "IRedirectResponse.h"
#include "core/base/IConvertUtil.h"
#include "core/base/ICodecUtil.h"

$PackageWebCoreBegin

IRedirectResponse::IRedirectResponse()
{
    raw->statusCode = IHttpStatus::FOUND_302;
}

IRedirectResponse::IRedirectResponse(const char *path)
{
    raw->statusCode = IHttpStatus::FOUND_302;
    this->setRedirectPath(path);
}

IRedirectResponse::IRedirectResponse(const QString &path)
{
    raw->statusCode = IHttpStatus::FOUND_302;
    this->setRedirectPath(path);
}

IRedirectResponse &IRedirectResponse::addAttribute(QString key, QString value)
{
    assert(!key.isEmpty() && !value.isEmpty());
    attributes[key] = value;

    updateLocationPath();
    return *this;
}

IRedirectResponse &IRedirectResponse::addAttribute(QMap<QString, QString> attribute)
{
    auto keys = attribute.keys();
    for(auto key : keys){
        attributes[key] = attribute[key];
    }

    updateLocationPath();
    return *this;
}

IRedirectResponse &IRedirectResponse::setRedirectPath(const QString &path)
{
    this->redirectPath = path;
    updateLocationPath();
    return *this;
}

void IRedirectResponse::setInstanceCopy(IResponseWare *ware)
{
    auto that = dynamic_cast<IRedirectResponse*>(ware);
    if(that == nullptr){
        qFatal("error with convertion, please check your code");
    }
    std::swap(that->raw, this->raw);
    std::swap(that->attributes, this->attributes);
    std::swap(that->redirectPath, this->redirectPath);
    updateLocationPath();
}

QString IRedirectResponse::getPrefixMatcher()
{
    return "$redirect:";
}

// TODO: 这里参数 encodeUri了， 那么url 需不需要 encode
// TODO: 这里把所有的字符都encode 掉吧
void IRedirectResponse::updateLocationPath()
{
    if(redirectPath.isEmpty()){
        return;
    }
    // 防止 非 acsii 字符，比如说汉字
    auto path = ICodecUtil::pathEncode(redirectPath);
    if(!attributes.isEmpty()){
        path.append('?');
        auto keys = attributes.keys();
        for(auto key : keys){
            path.append(ICodecUtil::urlEncode(key))
                    .append('=')
                    .append(ICodecUtil::urlEncode(attributes[key]));
        }
    }
    raw->headers["Location"] = path;
}

IRedirectResponse operator"" _redirect(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}

$PackageWebCoreEnd
