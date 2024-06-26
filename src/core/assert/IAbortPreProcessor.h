#pragma once

#include "core/base/IPreProcessorUtil.h"

#define PP_ABORT_FUNC(name) \
    public: \
    static void abort ## name(){    \
        instance()->abort(name);    \
    }

#define PP_ABORT_EXPAND_1(arg_0)  \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_2(arg_0, arg_1)  \
    PP_ABORT_EXPAND_1(arg_1) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_3(arg_0, arg_1, arg_2)  \
    PP_ABORT_EXPAND_2(arg_1, arg_2) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_4(arg_0, arg_1, arg_2, arg_3)  \
    PP_ABORT_EXPAND_3(arg_1, arg_2, arg_3) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_5(arg_0, arg_1, arg_2, arg_3, arg_4)  \
    PP_ABORT_EXPAND_4(arg_1, arg_2, arg_3, arg_4) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_6(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5)  \
    PP_ABORT_EXPAND_5(arg_1, arg_2, arg_3, arg_4, arg_5) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_7(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6)  \
    PP_ABORT_EXPAND_6(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_8(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7)  \
    PP_ABORT_EXPAND_7(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_9(arg_0, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8)  \
    PP_ABORT_EXPAND_8(arg_1, arg_2, arg_3, arg_4, arg_5, arg_6, arg_7, arg_8) \
    PP_ABORT_FUNC(arg_0)

#define PP_ABORT_EXPAND_(N) PP_ABORT_EXPAND_##N
#define PP_ABORT_EXPAND_EVAL(N) PP_ABORT_EXPAND_(N)
#define PP_ABORT_EXPAND(...) PP_EXPAND( PP_ABORT_EXPAND_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $AsAbort(...)   \
public: \
    enum Type{__VA_ARGS__, EndTag}; \
    PP_ABORT_EXPAND(__VA_ARGS__)
