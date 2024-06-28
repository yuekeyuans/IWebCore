﻿#include "IHttpAssert.h"

$PackageWebCoreBegin

void IHttpAssert1::loadAssert()
{
    addWarn("iresponse_setHeader_with_empty_value_or_key", "");
    addWarn("assamble_bean_when_bean_inner_parameter_not_found");

    addFatal("controller_invalid_parameter_type", "");

    addFatal("register_to_controllerManage_error", "you can not register anything when server is on");

    addFatal("UrlError", "url fragment should not contain . or ..", "please remove . or .. in url");
    addFatal("UrlBlankCharacter", "url has invalid character");
    addFatal("UrlInvalidCharacter",  "url has invalid character");
    addFatal("controller_check_param_Type_has_unsupported_user_defined_type");
    addFatal("controller_check_param_Type_has_unsupported_inner_type");
    addFatal("controller_method_get_but_want_body_content", "when in GET method, you can not use $Body or $Content to describe a parameter. because the body content is empty");
    addFatal("irequest_controller_function_with_param_not_marked");

    addFatal("MappingMismatchFatal", "$xxxMapping can`t match any function defined in controller","please check your route definition");
    addFatal("OverloadOrDefaultValueFunctionNotSupported"
             , "function that is overloaded or use default value in it`s arguments is not supported"
             , "the controller functions must not use overloaded function or default arguments");

    addFatal("error_in_register_status_with_code");
    addFatal("error_register_status_with_no_function", "In define Status Intercept, can not find a certain function");
    addFatal("register_status_not_allow_200_ok", "In define Status Intercept, status type are not allowed to be 200 (ok) ");
    addFatal("register_status_function_must_return_void", "In define Status Intercept, return type must be void");
    addFatal("register_status_param_must_be_specific", "In define Status Intercept, the parameter type must be IRequest& and IResponse&");

    addFatal("register_controller_do_not_use_singleton", "when you register a controller, you should use controller singleton, do not intialize your own instance");
    addFatal("unregister_controller_do_not_use_singleton", "when you unregister a controller, you should use controller singleton, do not intialize your own instance");

    addFatal("static_file_dir_not_exist", "your registered default static file dir not exist, please check");
    addFatal("static_file_dir_aleady_exist", "your registered default static file alreay exist, please check");
    addFatal("static_file_not_exist", "your returned file is not exist, please check");

    addFatal("http_mime_already_exist", "user register mime already exist, please duplicated this mime");
    addFatal("http_status_code_convert_failed", "number can not match any status code");

    addWarn("register_the_same_url", "registration can`t match the leaf or the leaf already exist");

    addWarn("process_void_return_with_request_not_set_mime_error");
    addWarn("process_void_return_with_request_not_set_status_error");

    // response
    addWarn("response_incorrect_append", "this type of response can not use append to enincrease content");
    addFatal("response_invalid_type_error", "all invalid type should be preprocessed before response to user");
}

$PackageWebCoreEnd
