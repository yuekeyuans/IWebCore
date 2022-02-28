#include "ControllerFatalAssertion.h"

$PackageWebCoreBegin

QString ControllerFatalAssertion::getAssertInfo()
{
    return R"(
[
    {
        "key" : "controller_invalid_parameter_type",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "irequest_getBodyParameter_with_invalid_mime",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "irequest_xml_currently_not_supported",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "controller_check_param_Type_has_unsupported_inner_type",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "controller_check_param_Type_has_unsupported_user_defined_type",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "controller_method_get_but_want_body_content",
        "reason": "",
        "description" : "when in GET method, you can not use $Body or $Content to describe a parameter. because the body content is empty",
        "solution" : ""
    }
]
    )";
}


$PackageWebCoreEnd
