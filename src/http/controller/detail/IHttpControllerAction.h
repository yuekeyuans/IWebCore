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
        String,
        Bean,
        IResponse,
    };

public:
    virtual void invoke(IRequest &req) const final;

public:
    IHttpMethod httpMethod;
    void* parentNode{nullptr};

    QString url;
    QList<IUrlFragmentNode> routeNode;  // TODO:
    IMethodNode methodNode;
};


// TODO: 这里写下使用的方法
inline void IHttpControllerAction::invoke(IRequest &request) const
{
    Q_UNUSED(request);
    // TODO: this will be intialized latter
}

$PackageWebCoreEnd
