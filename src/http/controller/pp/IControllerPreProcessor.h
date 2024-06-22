#pragma once

#include "core/base/IPreProcessorUtil.h"

#define $AsController(path) \
    Q_CLASSINFO(PP_STRING(iwebControllerMapping$), #path) \
private:

#define PP_CONTROLLER_PROP(funName, type, index)    \
    PP_STRING(iwebControllerFun ## $ ## funName ## $ ## type ## $ ## index)


#ifdef Q_MOC_RUN
    #define $Mixed(type, name)      type name##_$mixed
    #define $Param(type, name)      type name##_$param
    #define $Url(type, name)        type name##_$url
    #define $Body(type, name)       type name##_$body
    #define $Content(type, name)    type name##_$content
    #define $Header(type, name)     type name##_$header
    #define $Cookie(type, name)     type name##_$cookie
    #define $Session(type, name)    type name##_$session
    #define $Nullable(type, name)   type name##_$nullable
    #define $NotNull(type, name)    type name$$_$notnull

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

