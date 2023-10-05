#pragma once

#include "core/base/IPreProcessorUtil.h"
#include "core/context/IContextPreProcessor.h"

#define $AsController_1(klassName) \
    $UseInstance(klassName) \
private:

#define $AsController_2(klassName, path) \
    Q_CLASSINFO(PP_STRING(iwebControllerMapping$), #path) \
    $AsController_1(klassName)  \
private:

#define $AsController_(N) $AsController_##N
#define $AsController_EVAL(N) $AsController_(N)
#define $AsController(...) PP_EXPAND( $AsController_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
