#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/base/IMethodNode.h"
#include "http/base/IFunctionNode.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

// 所有的返回类型都统一成这个类型，
// 资源类型返回的是自定义的类型，这里之后会完善

// TODO:

struct IHttpRouteLeaf
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
