#pragma once

#define PP_CONTROLLER_STATUS_CODE_JOIN(funName, type) \
    PP_STRING( iwebControllerStatusCode$##funName##$##type)

#define $StatusCodeMapping(funName, code) \
    Q_CLASSINFO( PP_CONTROLLER_STATUS_CODE_JOIN(funName, reqFunName), #code) \
    Q_INVOKABLE

