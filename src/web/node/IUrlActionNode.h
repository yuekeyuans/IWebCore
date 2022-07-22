#pragma once

#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/node/IMethodNode.h"

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
};

$PackageWebCoreEnd
