#pragma once

#include "base/IPreProcessorUtil.h"

#define PP_STATUS_JOIN(funName, type) \
    PP_STRING( iwebStatusFun$##funName##$##type)

#define PP_STATUS_CONTROLLER(klassName) \
private:

#define $StatusMapping(funName, status) \
    Q_CLASSINFO( PP_STATUS_JOIN(funName, FunName), #funName) \
    Q_CLASSINFO( PP_STATUS_JOIN(funName, Status), #status)  \
    Q_INVOKABLE

#define $AsStatusController(klassName) \
public: \
    $UseInstance(klassName) \
    PP_STATUS_CONTROLLER(klassName) \
private:
