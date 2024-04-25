#include "IRedirectResponse.h"
#include "core/base/IConvertUtil.h"
#include "core/base/ICodecUtil.h"

$PackageWebCoreBegin

IRedirectResponse::IRedirectResponse()
{
    m_raw->statusCode = IHttpStatusCode::FOUND_302;
}

IRedirectResponse::IRedirectResponse(const char *path)
{
    m_raw->statusCode = IHttpStatusCode::FOUND_302;
    this->redirectPath = path;
    updateLocationPath();
}

IRedirectResponse::IRedirectResponse(const QString &path)
{
    m_raw->statusCode = IHttpStatusCode::FOUND_302;
    this->redirectPath = path;
    updateLocationPath();
}

IRedirectResponse::IRedirectResponse(IResponseWare *ware)
    : IResponseInterface(ware)
{
    auto that = dynamic_cast<IRedirectResponse*>(ware);
    if(that == nullptr){
        qFatal("error with convertion, please check your code");
    }
    std::swap(that->redirectPath, this->redirectPath);
    updateLocationPath();
}

//void IRedirectResponse::setInstanceCopy(IResponseWare *ware)
//{
//    auto that = dynamic_cast<IRedirectResponse*>(ware);
//    if(that == nullptr){
//        qFatal("error with convertion, please check your code");
//    }
//    std::swap(that->m_raw, this->m_raw);
//    std::swap(that->attributes, this->attributes);
//    std::swap(that->redirectPath, this->redirectPath);
//    updateLocationPath();
//}

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
    // 防止 非 acsii 字符，比如说汉字      //TODO: 这里是个啥， 需要看一下
    auto path = ICodecUtil::pathEncode(redirectPath);
//    if(!attributes.isEmpty()){
//        path.append('?');
//        auto keys = attributes.keys();
//        for(auto key : keys){
//            path.append(ICodecUtil::urlEncode(key))
//                    .append('=')
//                    .append(ICodecUtil::urlEncode(attributes[key]));
//        }
//    }
    m_raw->headers["Location"] = path;
}

IRedirectResponse operator"" _redirect(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}

$PackageWebCoreEnd
