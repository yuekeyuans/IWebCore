#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"
#include "IAssertManage.h"
#include "assertion/IAssertInfoList.h"

#define $AsAssertion(klassName) \
    $UseInstance(klassName)

#define $AssertFatal_1(key) \
        IAssertManage::fatal(PP_STRING(key));

#define $AssertFatal_2(key, extra) \
        IAssertManage::fatal(PP_STRING(key), extra);

#define $AssertFatal_(N) $AssertFatal_##N
#define $AssertFatal_EVAL(N) $AssertFatal_(N)
#define $AssertFatal(...) PP_EXPAND( $AssertFatal_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $AssertWarning_1(key) \
    IAssertManage::warn(PP_STRING(key));

#define $AssertWarning_2(key, extra) \
    IAssertManage::warn(PP_STRING(key), extra);

#define $AssertWarning_(N) $AssertWarning_##N
#define $AssertWarning_EVAL(N) $AssertWarning_(N)
#define $AssertWarning(...) PP_EXPAND( $AssertWarning_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

