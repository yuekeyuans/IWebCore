#pragma once

#include "core/util/IPreProcessorUtil.h"

#define $AsController(path) \
    Q_CLASSINFO(PP_STRING(IHttpControllerMapping$), #path) \
private:

#define PP_CONTROLLER_PROP(funName, type, index)    \
    PP_STRING(IHttpControllerFunMapping$$$ ## funName ## $$$ ## type ## $$$ ## index)

#ifdef Q_MOC_RUN
    #define $Query(name)      name##_$query
    #define $Path(name)        name##_$path
    #define $Body(name)       name##_$body
    #define $Content(name)    name##_$content
    #define $Header(name)     name##_$header
    #define $Cookie(name)     name##_$cookie
    #define $Session(name)    name##_$session
    #define $Optional(name)     name##_$optional

#else
    #define $Query(name)      name
    #define $Path(name)       name
    #define $Body(name)       name
    #define $Content(name)    name
    #define $Header(name)     name
    #define $Cookie(name)     name
    #define $Session(name)    name
    #define $Optional(name)   name

#endif

