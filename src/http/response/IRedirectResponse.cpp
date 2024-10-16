﻿#include "IRedirectResponse.h"
#include "core/util/ICodecUtil.h"

$PackageWebCoreBegin

IRedirectResponse::IRedirectResponse()
{
    m_raw->status = IHttpStatusCode::FOUND_302;
}

IRedirectResponse::IRedirectResponse(const QString &path)
{
    m_raw->status = IHttpStatusCode::FOUND_302;
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
    m_raw->headers.insert("Location", path);
}

IRedirectResponse operator"" _redirect(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}

$PackageWebCoreEnd
