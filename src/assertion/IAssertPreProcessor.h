#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"
#include "IAssertManage.h"
#include "assertion/IAssertInfoList.h"

#define $AsAssertion(klassName) \
    $UseInstance(klassName)

// TODO: 这里的Assert 之后要加上部分信息，信息包括 函数名称， 行数， 文件名称等信息
// 也加上 extra 信息

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

