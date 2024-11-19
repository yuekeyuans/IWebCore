#pragma once

#include "IControllerPreProcessor.h"

#define $PostMappingDeclare_1(funName)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 1), #funName)

#define $PostMappingDeclare_2(funName, url1)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 1), #url1)

#define $PostMappingDeclare_3(funName, url1, url2)  \
    $PostMappingDeclare(funName, url1) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 2), #url2)

#define $PostMappingDeclare_4(funName, url1, url2, url3)  \
    $PostMappingDeclare(funName, url1, url2) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 3), #url3)

#define $PostMappingDeclare_5(funName, url1, url2, url3, url4)  \
    $PostMappingDeclare(funName, url1, url2, url3) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 4), #url4)

#define $PostMappingDeclare_6(funName, url1, url2, url3, url4, url5)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 5), #url5)

#define $PostMappingDeclare_7(funName, url1, url2, url3, url4, url5, url6)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 6), #url6)

#define $PostMappingDeclare_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 7), #url7)

#define $PostMappingDeclare_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, POST, 8), #url8)

#define $PostMappingDeclare_(N) $PostMappingDeclare_##N
#define $PostMappingDeclare_EVAL(N) $PostMappingDeclare_(N)
#define $PostMappingDeclare(...) PP_EXPAND( $PostMappingDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $PostMapping_1(funName)  \
    $PostMappingDeclare(funName) \
    Q_INVOKABLE

#define $PostMapping_2(funName, url1)  \
    $PostMappingDeclare(funName, url1) \
    Q_INVOKABLE

#define $PostMapping_3(funName, url1, url2)  \
    $PostMappingDeclare(funName, url1, url2) \
    Q_INVOKABLE

#define $PostMapping_4(funName, url1, url2, url3)  \
    $PostMappingDeclare(funName, url1, url2, url3) \
    Q_INVOKABLE

#define $PostMapping_5(funName, url1, url2, url3, url4)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4) \
    Q_INVOKABLE

#define $PostMapping_6(funName, url1, url2, url3, url4, url5)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_INVOKABLE

#define $PostMapping_7(funName, url1, url2, url3, url4, url5, url6)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_INVOKABLE

#define $PostMapping_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_INVOKABLE

#define $PostMapping_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $PostMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7, url8) \
    Q_INVOKABLE

#define $PostMapping_(N) $PostMapping_##N
#define $PostMapping_EVAL(N) $PostMapping_(N)
#define $PostMapping(...) PP_EXPAND( $PostMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
