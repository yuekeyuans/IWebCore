#pragma once

#include "IControllerPreProcessor.h"

#define $DeleteMappingDeclare_1(funName)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 1), #funName)

#define $DeleteMappingDeclare_2(funName, url1)  \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 1), #url1)

#define $DeleteMappingDeclare_3(funName, url1, url2)  \
    $DeleteMappingDeclare_2(funName, url1) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 2), #url2)

#define $DeleteMappingDeclare_4(funName, url1, url2, url3)  \
    $DeleteMappingDeclare_3(funName, url1, url2) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 3), #url3)

#define $DeleteMappingDeclare_5(funName, url1, url2, url3, url4)  \
    $DeleteMappingDeclare_4(funName, url1, url2, url3) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 4), #url4)

#define $DeleteMappingDeclare_6(funName, url1, url2, url3, url4, url5)  \
    $DeleteMappingDeclare_5(funName, url1, url2, url3, url4) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 5), #url5)

#define $DeleteMappingDeclare_7(funName, url1, url2, url3, url4, url5, url6)  \
    $DeleteMappingDeclare_6(funName, url1, url2, url3, url4, url5) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 6), #url6)

#define $DeleteMappingDeclare_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $DeleteMappingDeclare_7(funName, url1, url2, url3, url4, url5, url6) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 7), #url7)

#define $DeleteMappingDeclare_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $DeleteMappingDeclare_8(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_CLASSINFO( PP_CONTROLLER_PROP(funName, DELETE, 8), #url8)

#define $DeleteMappingDeclare_(N) $DeleteMappingDeclare_##N
#define $DeleteMappingDeclare_EVAL(N) $DeleteMappingDeclare_(N)
#define $DeleteMappingDeclare(...) PP_EXPAND( $DeleteMappingDeclare_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define $DeleteMapping_1(funName)  \
    $DeleteMappingDeclare(funName) \
    Q_INVOKABLE

#define $DeleteMapping_2(funName, url1)  \
    $DeleteMappingDeclare(funName, url1) \
    Q_INVOKABLE

#define $DeleteMapping_3(funName, url1, url2)  \
    $DeleteMappingDeclare(funName, url1, url2) \
    Q_INVOKABLE

#define $DeleteMapping_4(funName, url1, url2, url3)  \
    $DeleteMappingDeclare(funName, url1, url2, url3) \
    Q_INVOKABLE

#define $DeleteMapping_5(funName, url1, url2, url3, url4)  \
    $DeleteMappingDeclare(funName, url1, url2, url3, url4) \
    Q_INVOKABLE

#define $DeleteMapping_6(funName, url1, url2, url3, url4, url5)  \
    $DeleteMappingDeclare(funName, url1, url2, url3, url4, url5) \
    Q_INVOKABLE

#define $DeleteMapping_7(funName, url1, url2, url3, url4, url5, url6)  \
    $DeleteMappingDeclare(funName, url1, url2, url3, url4, url5, url6) \
    Q_INVOKABLE

#define $DeleteMapping_8(funName, url1, url2, url3, url4, url5, url6, url7)  \
    $DeleteMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7) \
    Q_INVOKABLE

#define $DeleteMapping_9(funName, url1, url2, url3, url4, url5, url6, url7, url8)  \
    $DeleteMappingDeclare(funName, url1, url2, url3, url4, url5, url6, url7, url8) \
    Q_INVOKABLE

#define $DeleteMapping_(N) $DeleteMapping_##N
#define $DeleteMapping_EVAL(N) $DeleteMapping_(N)
#define $DeleteMapping(...) PP_EXPAND( $DeleteMapping_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
