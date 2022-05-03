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
    cause = R"(
{
    "debug":[

    ],
    "warn":[

    ],
    "error":[

    ],
    "fatal":[

    ]
}
)";

#endif
    return IJsonUtil::toJsonObject(cause);
}

$PackageWebCoreEnd
