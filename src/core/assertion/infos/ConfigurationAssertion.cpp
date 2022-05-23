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
    }
]
    )";
}

$PackageWebCoreEnd
