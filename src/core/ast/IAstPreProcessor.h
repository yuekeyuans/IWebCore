#pragma once

#include "IAstInfo.h"
#include "base/IJsonUtil.h"
#include "base/IMetaUtil.h"

#define $AsAst(klassName)   \
public:     \
    static klassName* instance(){   \
        static klassName inst;  \
        inst.load(IMetaUtil::getMetaClassName(klassName::staticMetaObject));    \
        return &inst;   \
    }   \
private:

#define $UseGlobalAst() \
    $UseAst(IGlobalAst, $GlobalAst)

#define $UseAst_1(klassName)  \
    static klassName* $Ast = klassName::instance();

#define $UseAst_2(klassName, name)  \
    static klassName* name = klassName::instance();

#define $UseAst_(N) $UseAst_##N
#define $UseAst_EVAL(N) $UseAst_(N)
#define $UseAst(...) PP_EXPAND( $UseAst_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
