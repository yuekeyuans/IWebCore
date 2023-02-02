#pragma once

#include "core/base/IPreProcessorUtil.h"

$PackageWebCoreBegin

    enum RequestParamType{
        Mixed,
        Url,
        Param,
        Header,
        Body,
        Cookie,
        Session,
        App,
        System,
        Attr
    };

$PackageWebCoreEnd

#define PP_FUN_PARAM_JOIN(funName) \
    PP_STRING(ignore_controller_fun_name_##funName)

#define $IgnoreAllParamWarn() \
    Q_CLASSINFO("ignore_all_controller_fun_name", "ALL");

#define $IgnoreParamWarn_1(funName)   \
    Q_CLASSINFO( PP_FUN_PARAM_JOIN(funName), #funName)

#define $IgnoreParamWarn_(N) $IgnoreParamWarn_##N
#define $IgnoreParamWarn_EVAL(N) $IgnoreParamWarn_(N)
#define $IgnoreParamWarn(...) PP_EXPAND( $IgnoreParamWarn_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#ifdef $SourceFile
    #define $Mixed(type, name)      type name
    #define $Param(type, name)      type name
    #define $Url(type, name)        type name
    #define $Body(type, name)       type name
    #define $Content(type, name)    type name
    #define $Header(type, name)     type name
    #define $Cookie(type, name)     type name
    #define $Session(type, name)    type name
    #define $App(type, name)        type name
    #define $System(type, name)     type name
    #define $Attr(type, name)       type name

#else
    #define $Mixed(type, name)      type name##_mixed
    #define $Param(type, name)      type name##_param
    #define $Url(type, name)        type name##_url
    #define $Body(type, name)       type name##_body
    #define $Content(type, name)    type name##_content
    #define $Header(type, name)     type name##_header
    #define $Cookie(type, name)     type name##_cookie
    #define $Session(type, name)    type name##_session
    #define $App(type, name)        type name##_app
    #define $System(type, name)     type name##_system
    #define $Attr(type, name)       type name##_attr
//    #define $Optional(type, name)   type name##_optional
#endif



// optional TODO: 这个也是之后支持， 表示这个参数是可选的， 相当于 spring 的 required = false
