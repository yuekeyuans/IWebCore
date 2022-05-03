#include "IControllerInterfaceDebug.h"
#include "base/IJsonUtil.h"

$PackageWebCoreBegin

IControllerInterfaceDebug::IControllerInterfaceDebug()
{
    loadConfigs();
}

QJsonObject IControllerInterfaceDebug::jsonFormatedInfo()
{
    QString cause;
#ifdef QT_DEBUG
    cause = R"({
"debug":[

],
"warn":[

],
"error":[

],
"fatal":[
    {
        "tag" : "UrlError",
        "reason": "url fragment should not contain . or ..",
        "solution": "please remove . or .. in url"
    },
    {
        "tag": "UrlInvalidCharacter":
        "reason": "url has invalid character",
    },
    {
        "tag": "UrlBlankCharacter":
        "reason": "url has invalid character",
    },
    {
        "tag": "OverloadOrDefaultValueFunctionNotSupported",
        "reason": " function that is overloaded or use default value in it`s arguments is not supported",
        "solution": "the controller functions must not use overloaded function or default arguments"
    },
    {
        "tag":"MappingMismatchFatal",
        "reason":"$xxxMapping can`t match any function defined in controller",
        "solution": "please check your route definition"
    }
]
})";

#endif
    return IJsonUtil::toJsonObject(cause);
}

$PackageWebCoreEnd
