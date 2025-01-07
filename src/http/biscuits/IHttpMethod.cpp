#include "IHttpMethod.h"

$PackageWebCoreBegin

IStringView IHttpMethodUtil::toString(IHttpMethod method)
{
    if(method >= IHttpMethod::UNKNOWN){
        method = IHttpMethod::UNKNOWN;
    }
    return methodNames()[static_cast<int>(method)].m_view;
}

IHttpMethod IHttpMethodUtil::toMethod(const QString &name)
{
    return toMethod(IStringView(name.toUtf8()));
}

IHttpMethod IHttpMethodUtil::toMethod(const IString& name)
{
    auto index = methodNames().indexOf(name);
    if(index >=0){
        return IHttpMethod(index);
    }
    return IHttpMethod::UNKNOWN;
}

const IStringList &IHttpMethodUtil::methodNames()
{
    static const IStringList m_methodNames = {
        "GET", "POST", "PUT", "DELETE",
        "PATCH", "HEAD", "OPTIONS", "UNKNOWN"
    };
    return m_methodNames;
}

$PackageWebCoreEnd
