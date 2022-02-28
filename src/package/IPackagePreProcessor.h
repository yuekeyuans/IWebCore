#pragma once

#include "base/IPreProcessorUtil.h"


#define $PackageBegin_1(name1) \
namespace name1 {


#define $PackageBegin_2(name1, name2) \
namespace name1 {   \
    namespace name2 {


#define $PackageBegin_(N) $PackageBegin_##N
#define $PackageBegin_EVAL(N) $PackageBegin_(N)
#define $PackageBegin(...) PP_EXPAND( $PackageBegin_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

////////////////

#define $PackageEnd_1(name1) \
}

#define $PackageEnd_2(name1, name2) \
    }   \
}

#define $PackageEnd_(N) $PackageEnd_##N
#define $PackageEnd_EVAL(N) $PackageEnd_(N)
#define $PackageEnd(...) PP_EXPAND( $PackageEnd_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

//////////////////

#define $PackageUsing_1(name1) \
    using namespace name1;

#define $PackageUsing_(N) $PackageUsing_##N
#define $PackageUsing_EVAL(N) $PackageUsing_(N)
#define $PackageUsing(...) PP_EXPAND( $PackageUsing_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $PackageWebCoreBegin \
    $PackageBegin(IWebCore)

#define $PackageWebCoreEnd \
    $PackageEnd(IWebCore)

#define $PackageWebCoreUsing \
    $PackageUsing(IWebCore)

#define $PackageWebCoreName ("IWebCore")
