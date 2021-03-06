#pragma once

#include "base/IHeaderUtil.h"
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
    void* parentNode{nullptr};
    bool  ignoreParamCheck{false};
    QString url;
    IHttpMethod httpMethod;

    Type type {Method};
    IMethodNode methodNode;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd
