#pragma once

#include "IAssetInfo.h"
#include "base/IJsonUtil.h"
#include "base/IMetaUtil.h"

#define $AsAsset(klassName)   \
public:     \
    static klassName* instance(){   \
        static klassName inst;  \
        inst.load(IMetaUtil::getMetaClassName(klassName::staticMetaObject));    \
        return &inst;   \
    }   \
private:

#define $UseGlobalAsset() \
    $UseAsset(IGlobalAsset, $GlobalAsset)

#define $UseAsset_1(klassName)  \
    static klassName* $Ast = klassName::instance();

#define $UseAsset_2(klassName, name)  \
    static klassName* name = klassName::instance();

#define $UseAsset_(N) $UseAsset_##N
#define $UseAsset_EVAL(N) $UseAsset_(N)
#define $UseAsset(...) PP_EXPAND( $UseAsset_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
