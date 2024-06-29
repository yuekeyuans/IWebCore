#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/node/IMethodNode.h"
#include "http/node/IFunctionNode.h"

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
