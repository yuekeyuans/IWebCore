#pragma once

#include "core/base/IPreProcessorUtil.h"

#define PP_CONTROLLER_JOIN(funName, type) \
    PP_STRING( iwebControllerFun$##funName##$##type)

#define $PutMappingDeclare_1(funName)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #funName)

#define $PutMappingDeclare_2(funName, url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)

#define $PutMappingDeclare_3(funName, url1, url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)

#define $PutMappingDeclare_4(funName, url1, url2, url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)

#define $PutMappingDeclare_5(funName, url1, url2, url3, url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)

#define $PutMappingDeclare_6(funName, url1, url2, url3, url4, url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)

#define $PutMappingDeclare_7(funName, url1, url2, url3, url4, url5, url6)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 6), #url6)

#define $PutMappingDeclare_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 6), #url6)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 7), #url7)

#define $PutMappingDeclare_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, resFunName), #funName) \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, reqMethod), "PUT")  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 1), #url1)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 2), #url2)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 3), #url3)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 4), #url4)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 5), #url5)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 6), #url6)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 7), #url7)  \
    Q_CLASSINFO( PP_CONTROLLER_JOIN(funName, 8), #url8)

#define $PutMappingDeclare_(N) $PutMappingDeclare_##N
#define $PutMappingDeclare_EVAL(N) $PutMappingDeclare_(N)
#define $PutMappingDeclare(...) PP_EXPAND( $PutMappingDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $PutMapping_1(funName)  \
    $PutMappingDeclare(funName) \
    Q_INVOKABLE

#define $PutMapping_2(funName, url1)  \
    $PutMappingDeclare(funName, url1) \
    Q_INVOKABLE

#define $PutMapping_3(funName, url1, url2)  \
    $PutMappingDeclare(funName, url1, url2) \
    Q_INVOKABLE

#define $PutMapping_4(funName, url1, url2, url3)  \
    $PutMappingDeclare(funName, url1, url2, url3) \
    Q_INVOKABLE

#define $PutMapping_5(funName, url1, url2, url3, url4)  \
    $PutMappingDeclare(funName, url1, url2, url3, url4) \
    Q_INVOKABLE

#define $PutMapping_6(funName, url1, url2, url3, url4, url5)  \
    $PutMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_INVOKABLE

#define $PutMapping_7(funName, url1, url2, url3, url4, url5, url6)  \
    $PutMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_INVOKABLE

#define $PutMapping_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $PutMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_INVOKABLE

#define $PutMapping_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $PutMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7, url8) \
    Q_INVOKABLE

#define $PutMapping_(N) $PutMapping_##N
#define $PutMapping_EVAL(N) $PutMapping_(N)
#define $PutMapping(...) PP_EXPAND( $PutMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


