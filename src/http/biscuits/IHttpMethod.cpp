#include "IHttpMethod.h"

$PackageWebCoreBegin

QString IHttpMethodUtil::toString(IHttpMethod method)
{
    if(method >= IHttpMethod::UNKNOWN){
        method = IHttpMethod::UNKNOWN;
    }
    return methodNames()[static_cast<int>(method)];
}

IHttpMethod IHttpMethodUtil::toMethod(const QString &name)
{
    auto index = methodNames().indexOf(name.toUpper());
    if(index == -1){
        return IHttpMethod::UNKNOWN;
    }
    return static_cast<IHttpMethod>(index);
}

IHttpMethod IHttpMethodUtil::toMethod(std::string_view name)
{
    return toMethod(QString::fromLocal8Bit(name.data(), name.length()));
}

const QStringList &IHttpMethodUtil::methodNames()
{
    static const QStringList m_methodNames = {"GET", "POST", "PUT", "DELETE", "PATCH", "HEAD", "OPTIONS", "UNKNOWN"};
    return m_methodNames;
}



$PackageWebCoreEnd
