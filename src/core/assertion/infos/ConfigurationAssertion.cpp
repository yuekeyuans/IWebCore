#include "ConfigurationAssertion.h"

$PackageWebCoreBegin

QString ConfigurationAssertion::getAssertInfo()
{
    return R"(
[
    {
        "key" : "configuration_json_resolve_fatal",
        "reason": "",
        "description" : "",
        "solution" : ""
    }
]
    )";
}

$PackageWebCoreEnd
