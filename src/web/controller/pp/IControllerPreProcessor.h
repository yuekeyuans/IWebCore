#pragma once

#include "core/base/IPreProcessorUtil.h"

#define $AsController(path) \
    Q_CLASSINFO(PP_STRING(iwebControllerMapping$), #path) \
private:

#define PP_CONTROLLER_PROP(funName, type, index)    \
    PP_STRING(iwebControllerFun ## $ ## funName ## $ type ## $ ## index)
