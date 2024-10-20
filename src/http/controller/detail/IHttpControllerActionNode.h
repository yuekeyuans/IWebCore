#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/base/IMethodNode.h"
#include "http/base/IFunctionNode.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

struct IHttpControllerActionNode
{
    enum class ReturnType{
        Void,
//        Int,
        String,
        Bean,
        IResponse,
    };

    enum class CallableType{
        Method,
        Function
    };

public:
    IHttpMethod httpMethod;
    CallableType type {CallableType::Method};
    void* parentNode{nullptr};

    QString url;
    QList<IUrlFragmentNode> routeNode;  // TODO:
    IMethodNode methodNode;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd
