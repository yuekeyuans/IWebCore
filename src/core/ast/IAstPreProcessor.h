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

#define $UseAst(klassName)  \
private:    \
    klassName##Ast* $Ast = klassName##Ast::instance();  \
private:
