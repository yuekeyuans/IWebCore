#pragma once

#include "base/IPreProcessorUtil.h"

#define PP_CONTROLLER_JOIN(funName, type) \
    PP_STRING( iwebControllerFun$##funName##$##type)

/// 当 只用一个参数的时候，匹配当前controller 对应的内容
#define $PostMapping_1(funName)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), "/")  \
    Q_INVOKABLE

#define $PostMapping_2(funName, url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_INVOKABLE


#define $PostMapping_3(funName, url1, url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_INVOKABLE

#define $PostMapping_4(funName, url1, url2, url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_INVOKABLE

#define $PostMapping_5(funName, url1, url2, url3, url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_INVOKABLE

#define $PostMapping_6(funName, url1, url2, url3, url4, url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_INVOKABLE

#define $PostMapping_7(funName, url1, url2, url3, url4, url5, url6)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 6), #url6)  \
    Q_INVOKABLE

#define $PostMapping_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 6), #url6)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 7), #url7)  \
    Q_INVOKABLE

#define $PostMapping_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "POST")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 6), #url6)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 7), #url7)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 8), #url8)  \
    Q_INVOKABLE


#define $PostMapping_(N) $PostMapping_##N
#define $PostMapping_EVAL(N) $PostMapping_(N)
#define $PostMapping(...) PP_EXPAND( $PostMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
