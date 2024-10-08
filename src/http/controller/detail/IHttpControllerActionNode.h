#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/base/IMethodNode.h"
#include "http/base/IFunctionNode.h"

$PackageWebCoreBegin

struct IHttpControllerActionNode{

public:
    enum Type{
        Method,
        Function
    };
public:
    IHttpMethod httpMethod;
    Type type {Method};
    void* parentNode{nullptr};
    
    QString url;
    IMethodNode methodNode;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd
