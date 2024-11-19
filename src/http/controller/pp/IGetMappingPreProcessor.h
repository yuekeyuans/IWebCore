﻿#pragma once

#include "IControllerPreProcessor.h"

#define $GetMappingDeclare_1(funName)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 1), #funName)

#define $GetMappingDeclare_2(funName, url1)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 1), #url1)

#define $GetMappingDeclare_3(funName, url1, url2)  \
    $GetMappingDeclare(funName, url1) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 2), #url2)

#define $GetMappingDeclare_4(funName, url1, url2, url3)  \
    $GetMappingDeclare(funName, url1, url2) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 3), #url3)

#define $GetMappingDeclare_5(funName, url1, url2, url3, url4)  \
    $GetMappingDeclare(funName, url1, url2, url3) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 4), #url4)

#define $GetMappingDeclare_6(funName, url1, url2, url3, url4, url5)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 5), #url5)

#define $GetMappingDeclare_7(funName, url1, url2, url3, url4, url5, url6)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 6), #url6)

#define $GetMappingDeclare_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 7), #url7)

#define $GetMappingDeclare_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, GET, 8), #url8)

#define $GetMappingDeclare_(N) $GetMappingDeclare_##N
#define $GetMappingDeclare_EVAL(N) $GetMappingDeclare_(N)
#define $GetMappingDeclare(...) PP_EXPAND( $GetMappingDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define $GetMapping_1(funName)  \
    $GetMappingDeclare(funName) \
    Q_INVOKABLE

#define $GetMapping_2(funName, url1)  \
    $GetMappingDeclare(funName, url1) \
    Q_INVOKABLE

#define $GetMapping_3(funName, url1, url2)  \
    $GetMappingDeclare(funName, url1, url2) \
    Q_INVOKABLE

#define $GetMapping_4(funName, url1, url2, url3)  \
    $GetMappingDeclare(funName, url1, url2, url3) \
    Q_INVOKABLE

#define $GetMapping_5(funName, url1, url2, url3, url4)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4) \
    Q_INVOKABLE

#define $GetMapping_6(funName, url1, url2, url3, url4, url5)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_INVOKABLE

#define $GetMapping_7(funName, url1, url2, url3, url4, url5, url6)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_INVOKABLE

#define $GetMapping_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_INVOKABLE

#define $GetMapping_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $GetMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7, url8) \
    Q_INVOKABLE

#define $GetMapping_(N) $GetMapping_##N
#define $GetMapping_EVAL(N) $GetMapping_(N)
#define $GetMapping(...) PP_EXPAND( $GetMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
