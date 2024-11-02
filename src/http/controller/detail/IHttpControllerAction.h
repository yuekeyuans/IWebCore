#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/base/IMethodNode.h"
#include "http/base/IFunctionNode.h"
#include "http/mappings/IHttpAction.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

struct IHttpControllerAction : public IHttpActionInterface
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
    virtual void invoke(IRequest &req) final;

public:
    IHttpMethod httpMethod;
    CallableType type {CallableType::Method};
    void* parentNode{nullptr};

    QString url;
    QList<IUrlFragmentNode> routeNode;  // TODO:
    IMethodNode methodNode;
    IFunctionNode functionNode;

    // IHttpAction interface
};

inline void IHttpControllerAction::invoke(IRequest &request)
{
    // TODO: this will be intialized latter
}

$PackageWebCoreEnd
