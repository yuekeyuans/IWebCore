#pragma once

#include "core/base/IHeaderUtil.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/node/IMethodNode.h"
#include "web/node/IFunctionNode.h"

$PackageWebCoreBegin

struct IUrlActionNode{

public:
    enum Type{
        Method,
        Function
    };
public:
    IHttpMethod httpMethod;
    Type type {Method};
    void* parentNode{nullptr};
    bool  ignoreParamCheck{false};
    
    QString url;
    IMethodNode methodNode;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd
