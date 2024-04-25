#include "IHttpStatus.h"

$PackageWebCoreBegin

QString IHttpStatus::toString(const IHttpStatusCode status)
{
    return QString::number(static_cast<int>(status));
}

QString IHttpStatus::toStringDescription(IHttpStatusCode code)
{
    QString name = QMetaEnum::fromType<IHttpStatusCode>().valueToKey(code);
    return name.split("_").join(" ").toLower();
}

IHttpStatusCode IHttpStatus::toStatus(int code)
{
    if(!contain(code)){
        return UNKNOWN;
    }
    return IHttpStatusCode(code);
}

IHttpStatusCode IHttpStatus::toStatus(const QString &number)
{
    bool ok;
    auto value = number.toInt(&ok);
    if(!ok){
        return Code::UNKNOWN;
    }
    return toStatus(value);
}

bool IHttpStatus::contain(int code)
{
    return QMetaEnum::fromType<IHttpStatusCode>().valueToKey(code) != nullptr;
}

$PackageWebCoreEnd
