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
    },
    {
        "key" : "merge_json_config_value_error",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "EnableBluePrint_param_error",
        "reason": "$EnableBluePrint has parameter that is not bool type",
        "description" : "",
        "solution" : ""
    }
]
    )";
}

$PackageWebCoreEnd
