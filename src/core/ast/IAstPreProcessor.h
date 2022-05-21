#pragma once

#include "IAstInfo.h"
#include "base/IJsonUtil.h"

#define $AsAst(klassName)   \
public:     \
    static klassName* instance(){   \
        static klassName inst;  \
        inst.load();    \
        return &inst;   \
    }   \
private:
