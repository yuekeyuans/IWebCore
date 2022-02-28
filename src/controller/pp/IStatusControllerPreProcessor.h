#pragma once

#include "base/IPreProcessorUtil.h"

#define PP_STATUS_JOIN(funName, type) \
    PP_STRING( iwebStatusFun$##funName##$##type)

#define PP_STATUS_CONTROLLER(klassName) \
public: \
    virtual void registerControllerFun(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods) final {    \
        auto nodes = IStatusControllerInterfaceImpl::generateStatusFunctionNodes(handler, clsInfo, methods);    \
        IStatusControllerInterfaceImpl::checkStatusNodes(nodes);    \
        IControllerManage::registerStatusFunctions(nodes);  \
    }   \
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
