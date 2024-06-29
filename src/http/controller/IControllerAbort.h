#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IControllerAbort : public IAbortInterface<IControllerAbort>
{
    $AsAbort(
        OverloadOrDefaultValueFunctionNotSupported,
        MappingMismatchFatal,
        UrlInvalidCharacter,
        UrlError,
        UrlBlankCharacter,
        controller_check_param_Type_has_unsupported_inner_type,
        controller_check_param_Type_has_unsupported_user_defined_type,
        controller_method_get_but_want_body_content,
        irequest_controller_function_with_param_not_marked,
        assamble_bean_when_bean_inner_parameter_not_found,
        static_file_dir_not_exist,
        register_the_same_url,
        register_to_controllerManage_error,
        register_controller_do_not_use_singleton
    )

protected:
    virtual QMap<int, QString> abortDescription() const {
        return {
            {OverloadOrDefaultValueFunctionNotSupported, "function that is overloaded or use default value in it`s arguments is not supported. the controller functions must not use overloaded function or default arguments"}
            ,{MappingMismatchFatal, "$xxxMapping can`t match any function defined in controller. please check your route definition"}
            ,{UrlInvalidCharacter,  "url has invalid character"}
            ,{UrlError, "url fragment should not contain . or .. , please remove . or .. in url"}
            ,{UrlBlankCharacter, "url has invalid character"}
            ,{controller_check_param_Type_has_unsupported_inner_type, ""}   // TODO:
            ,{controller_check_param_Type_has_unsupported_user_defined_type, ""}    // TODO:
            ,{controller_method_get_but_want_body_content, "when in GET method, you can not use $Body or $Content to describe a parameter. because the body content is empty"}
            ,{irequest_controller_function_with_param_not_marked, ""}
            ,{assamble_bean_when_bean_inner_parameter_not_found, ""}
            ,{static_file_dir_not_exist, "your registered default static file dir not exist, please check"}
            ,{register_the_same_url, "registration can`t match the leaf or the leaf already exist"}
            ,{register_to_controllerManage_error, "you can not register anything when server is on"}
            ,{register_controller_do_not_use_singleton, "when you register a controller, you should use controller singleton, do not intialize your own instance"}
        };
    }
};

$PackageWebCoreEnd
