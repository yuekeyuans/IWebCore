#pragma once

#include "core/util/IPreProcessorUtil.h"

#define $AsController(path) \
    Q_CLASSINFO(PP_STRING(IHttpControllerMapping$), #path) \
private:

#define PP_CONTROLLER_PROP(funName, type, index)    \
    PP_STRING(IHttpControllerFunMapping$ ## funName ## $ ## type ## $ ## index)


#ifdef Q_MOC_RUN
    #define $Mixed(name)      name##_$mixed
    #define $Query(name)      name##_$query
    #define $Path(name)        name##_$path
    #define $Body(name)       name##_$body
    #define $Content(name)    name##_$content
    #define $Header(name)     name##_$header
    #define $Cookie(name)     name##_$cookie
    #define $Session(name)    name##_$session
    #define $Nullable(name)   name##_$nullable
    #define $NotNull(name)    name$$_$notnull

#else
    #define $Mixed(name)      name
    #define $Query(name)      name
    #define $Path(name)       name
    #define $Body(name)       name
    #define $Content(name)    name
    #define $Header(name)     name
    #define $Cookie(name)     name
    #define $Session(name)    name
    #define $Nullable(name)   name
    #define $NotNull(name)    name

#endif

