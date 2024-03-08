#pragma once

#include "IControllerPreProcessor.h"

#define $PatchMappingDeclare_1(funName)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 1), #funName)

#define $PatchMappingDeclare_2(funName, url1)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 1), #url1)

#define $PatchMappingDeclare_3(funName, url1, url2)  \
    $PatchMappingDeclare(funName, url1) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 2), #url2)

#define $PatchMappingDeclare_4(funName, url1, url2, url3)  \
    $PatchMappingDeclare(funName, url1, url2) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 3), #url3)

#define $PatchMappingDeclare_5(funName, url1, url2, url3, url4)  \
    $PatchMappingDeclare(funName, url1, url2, url3) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 4), #url4)

#define $PatchMappingDeclare_6(funName, url1, url2, url3, url4, url5)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 5), #url5)

#define $PatchMappingDeclare_7(funName, url1, url2, url3, url4, url5, url6)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 6), #url6)

#define $PatchMappingDeclare_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 7), #url7)

#define $PatchMappingDeclare_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, PATCH, 8), #url8)

#define $PatchMappingDeclare_(N) $PatchMappingDeclare_##N
#define $PatchMappingDeclare_EVAL(N) $PatchMappingDeclare_(N)
#define $PatchMappingDeclare(...) PP_EXPAND( $PatchMappingDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $PatchMapping_1(funName)  \
    $PatchMappingDeclare(funName) \
    Q_INVOKABLE

#define $PatchMapping_2(funName, url1)  \
    $PatchMappingDeclare(funName, url1) \
    Q_INVOKABLE

#define $PatchMapping_3(funName, url1, url2)  \
    $PatchMappingDeclare(funName, url1, url2) \
    Q_INVOKABLE

#define $PatchMapping_4(funName, url1, url2, url3)  \
    $PatchMappingDeclare(funName, url1, url2, url3) \
    Q_INVOKABLE

#define $PatchMapping_5(funName, url1, url2, url3, url4)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4) \
    Q_INVOKABLE

#define $PatchMapping_6(funName, url1, url2, url3, url4, url5)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_INVOKABLE

#define $PatchMapping_7(funName, url1, url2, url3, url4, url5, url6)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_INVOKABLE

#define $PatchMapping_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_INVOKABLE

#define $PatchMapping_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $PatchMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7, url8) \
    Q_INVOKABLE

#define $PatchMapping_(N) $PatchMapping_##N
#define $PatchMapping_EVAL(N) $PatchMapping_(N)
#define $PatchMapping(...) PP_EXPAND( $PatchMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
