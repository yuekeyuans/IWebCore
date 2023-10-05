#pragma once

#include "IAssertInfo.h"
#include "core/base/IJsonUtil.h"
#include "core/base/IMetaUtil.h"

#define $AsAssert(klassName)   \
public:     \
    static klassName* instance(){   \
        static klassName inst;  \
        static std::once_flag flag;     \
        std::call_once(flag, [&](){ \
                inst.loadAssert();    \
        }); \
        return &inst;   \
    }   \
private:

#define $UseGlobalAssert() \
    $UseAssert(IGlobalAssert, $GlobalAssert)

#define $UseAssert_1(klassName)  \
    static klassName* $Ast = klassName::instance();

#define $UseAssert_2(klassName, name)  \
    static klassName* name = klassName::instance();

#define $UseAssert_(N) $UseAssert_##N
#define $UseAssert_EVAL(N) $UseAssert_(N)
#define $UseAssert(...) PP_EXPAND( $UseAssert_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
