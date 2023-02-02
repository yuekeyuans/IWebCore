#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IPreProcessorUtil.h"

#define $AsMiddleWare_1(klassName)    \
    $UseInstance(klassName) \
public: \
    using IMiddleWare::operator();  \
    virtual QString name() final {return #klassName ; };    \
private:

#define $AsMiddleWare_2(klassName, middleWareName)    \
    $UseInstance(klassName) \
public: \
    using IMiddleWare::operator();  \
    virtual QString name() final {return #middleWareName ; };   \
private:

#define $AsMiddleWare_(N) $AsMiddleWare_##N
#define $AsMiddleWare_EVAL(N) $AsMiddleWare_(N)
#define $AsMiddleWare(...) PP_EXPAND( $AsMiddleWare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

