#pragma once

#include "http/biscuits/IHttpMethod.h"
#include "http/base/IMethodNode.h"
//#include "http/base/IFunctionNode.h"
#include "http/mappings/IHttpActionInterface.h"
#include "http/controller/detail/IHttpUrlFragment.h"

$PackageWebCoreBegin

struct IHttpControllerAction : public IHttpActionInterface<IHttpControllerAction>
{
//    enum class ReturnType{
//        Void,
//        String,
//        Bean,
//        IResponse,
//    };

public:
    virtual void invoke(IRequest &req) const final;

public:
    IHttpMethod httpMethod;
    void* parentNode{nullptr};

    QString url;
    QList<IHttpUrlFragment> routeNode;  // TODO:
    IMethodNode methodNode;
};

$PackageWebCoreEnd
