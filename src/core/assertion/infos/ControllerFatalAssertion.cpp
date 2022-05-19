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
    },
    {
        "key" : "error_in_register_status_with_code",
        "reason": "",
        "description" :"",
        "solution" : ""
    },
    {
        "key" : "error_register_status_with_no_function",
        "reason": "",
        "description" :"In define Status Intercept, can not find a certain function",
        "solution" : ""
    },
    {
        "key" : "register_status_not_allow_200_ok",
        "reason": "",
        "description" :"In define Status Intercept, status type are not allowed to be 200 (ok) ",
        "solution" : ""
    },
    {
        "key" : "register_status_function_must_return_void",
        "reason": "",
        "description" :"In define Status Intercept, return type must be void",
        "solution" : ""
    },
    {
        "key" : "register_status_param_must_be_specific",
        "reason": "",
        "description" :"In define Status Intercept, the parameter type must be IRequest& and IResponse&",
        "solution" : ""
    }
]
    )";
}


$PackageWebCoreEnd
