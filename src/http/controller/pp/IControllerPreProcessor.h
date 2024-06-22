#pragma once

#include "core/base/IPreProcessorUtil.h"

#define $AsController(path) \
    Q_CLASSINFO(PP_STRING(iwebControllerMapping$), #path) \
private:

#define PP_CONTROLLER_PROP(funName, type, index)    \
    PP_STRING(iwebControllerFun ## $ ## funName ## $ ## type ## $ ## index)


#ifdef Q_MOC_RUN
    #define $Mixed(type, name)      type name##_mixed
    #define $Param(type, name)      type name##_param
    #define $Url(type, name)        type name##_url
    #define $Body(type, name)       type name##_body
    #define $Content(type, name)    type name##_content
    #define $Header(type, name)     type name##_header
    #define $Cookie(type, name)     type name##_cookie
    #define $Session(type, name)    type name##_session
    #define $Nullable(type, name)   type name##_nullable
    #define $NotNull(type, name)    type name$$_notnull

#else
    #define $Mixed(type, name)      type name
    #define $Param(type, name)      type name
    #define $Url(type, name)        type name
    #define $Body(type, name)       type name
    #define $Content(type, name)    type name
    #define $Header(type, name)     type name
    #define $Cookie(type, name)     type name
    #define $Session(type, name)    type name
    #define $Nullable(type, name)   type name
    #define $NotNull(type, name)    type name

#endif

