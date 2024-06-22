#pragma once

#include "core/base/IPreProcessorUtil.h"

#define $AsController(path) \
    Q_CLASSINFO(PP_STRING(iwebControllerMapping$), #path) \
private:

#define PP_CONTROLLER_PROP(funName, type, index)    \
    PP_STRING(iwebControllerFun ## $ ## funName ## $ ## type ## $ ## index)


#ifdef Q_MOC_RUN
    #define $Mixed(name)      name##_$mixed
    #define $Param(name)      name##_$param
    #define $Url(name)        name##_$url
    #define $Body(name)       name##_$body
    #define $Content(name)    name##_$content
    #define $Header(name)     name##_$header
    #define $Cookie(name)     name##_$cookie
    #define $Session(name)    name##_$session
    #define $Nullable(name)   name##_$nullable
    #define $NotNull(name)    name$$_$notnull

#else
    #define $Mixed(name)      name
    #define $Param(name)      name
    #define $Url(name)        name
    #define $Body(name)       name
    #define $Content(name)    name
    #define $Header(name)     name
    #define $Cookie(name)     name
    #define $Session(name)    name
    #define $Nullable(name)   name
    #define $NotNull(name)    name

#endif

