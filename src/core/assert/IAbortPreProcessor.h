#pragma once

#include "core/base/IPreProcessorUtil.h"

#define PP_ABORT_EXPAND_1(funName)  \

#define PP_ABORT_EXPAND_2(funName, url1)  \

#define PP_ABORT_EXPAND_3(funName, url1, url2)  \

#define PP_ABORT_EXPAND_4(funName, url1, url2, url3)  \

#define PP_ABORT_EXPAND_5(funName, url1, url2, url3, url4)  \

#define PP_ABORT_EXPAND_6(funName, url1, url2, url3, url4, url5)  \

#define PP_ABORT_EXPAND_7(funName, url1, url2, url3, url4, url5, url6)  \

#define PP_ABORT_EXPAND_8(funName, url1, url2, url3, url4, url5, url6, url7)  \

#define PP_ABORT_EXPAND_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \

#define PP_ABORT_EXPAND_(N) PP_ABORT_EXPAND_##N
#define PP_ABORT_EXPAND_EVAL(N) PP_ABORT_EXPAND_(N)
#define PP_ABORT_EXPAND(...) PP_EXPAND( PP_ABORT_EXPAND_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $AsAbort(...)   \
    enum Type{__VA_ARGS__}; \
    PP_ABORT_EXPAND(__VA_ARGS__)
