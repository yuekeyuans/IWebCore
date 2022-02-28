#pragma once

#include "base/IPreProcessorUtil.h"
#include "configuration/IConfigurationPreProcessor.h"

#define PP_CONTROLLER(klassName) \
protected: \
    virtual void registerControllerFun(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaMethod> &methods) final {    \
        IControllerInterfaceImplProxy::checkUrlMappings(handler, clsInfo, methods);  \
        auto functionNodes = IControllerInterfaceImplProxy::createMappingLeaves(handler, clsInfo, methods);  \
        if(!functionNodes.empty()){ \
            IControllerManage::registerUrlFunctions(functionNodes); \
        }   \
    }   \
private:

#define $AsController_1(klassName) \
    $UseConfig(klassName) \
    $UseInstance(klassName) \
    PP_CONTROLLER(klassName)    \
private:

#define $AsController_2(klassName, path) \
    Q_CLASSINFO(PP_STRING(iwebControllerMapping$), #path) \
    $AsController_1(klassName)  \
private:

#define $AsController_(N) $AsController_##N
#define $AsController_EVAL(N) $AsController_(N)
#define $AsController(...) PP_EXPAND( $AsController_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
