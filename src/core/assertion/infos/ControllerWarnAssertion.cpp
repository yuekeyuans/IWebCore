#include "ControllerWarnAssertion.h"

$PackageWebCoreBegin

QString ControllerWarnAssertion::getAssertInfo()
{

        return R"(
[
    {
        "key" : "process_void_return_with_request_not_set_mime_error",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "process_void_return_with_request_not_set_status_error",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "checkDumplicatedParameters_find_More_than_one_value",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "irequest_get_parameter_in_body_with_mime_text",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "irequest_controller_function_with_param_not_marked",
        "reason": "",
        "description" : "",
        "solution" : ""
    },
    {
        "key" : "assamble_bean_when_bean_inner_parameter_not_found",
        "reason": "",
        "description" : "",
        "solution" : ""
    }
]
    )";
}

$PackageWebCoreEnd
