#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"

#define $AsMiddleWare_1(klassName)    \
    $UseInstance(klassName) \
    virtual QString name() final {return #klassName ; };

#define $AsMiddleWare_2(klassName, middleWareName)    \
    $UseInstance(klassName) \
    virtual QString name() final {return #middleWareName ; };

#define $AsMiddleWare_(N) $AsMiddleWare_##N
#define $AsMiddleWare_EVAL(N) $AsMiddleWare_(N)
#define $AsMiddleWare(...) PP_EXPAND( $AsMiddleWare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

