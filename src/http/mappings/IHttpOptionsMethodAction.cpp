#include "IHttpOptionsMethodAction.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/response/IResponseWare.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/IHttpManage.h"
#include "IHttpNotFoundAction.h"
#include "IHttpInvalidRequestAction.h"

$PackageWebCoreBegin

// TODO: 这里实现不涉及 跨域问题, 之后补充
void IHttpOptionsMethodAction::invoke(IRequest &request) const
{
    if(request.url() == "*"){
        IResponseWare ware;
        ware.setHeader(IHttpHeader::Allow, AllowContent);
        request.impl().setResponseWare(std::move(ware));
    }else{
        processUrlOptions(request);
    }
    request.doWrite();
}

void IHttpOptionsMethodAction::processUrlOptions(IRequest& request) const
{
    static const QList<IHttpMethod> METHODS = {
        IHttpMethod::GET, IHttpMethod::POST, IHttpMethod::PUT,
        IHttpMethod::DELETED, IHttpMethod::HEAD, IHttpMethod::PATCH
    };

    IStringViewList views;
    for(auto method : METHODS){
        request.impl().m_reqRaw.m_method = method;
        auto action = IHttpManage::instance()->getAction(request);
        if(action != IHttpNotFoundAction::instance()
                && action != IHttpInvalidRequestAction::instance()){
            views.append(IHttpMethodUtil::toString(method));
        }
    }
    request.impl().m_reqRaw.m_method = IHttpMethod::OPTIONS;

    if(views.isEmpty()){
        request.setInvalid(IHttpNotFoundInvalid());
    }else{
        views.append(IHttpMethodUtil::toString(IHttpMethod::OPTIONS));
        auto ret = request.stash(views.join(", "));
        IResponseWare ware;
        ware.setHeader(IHttpHeader::Allow, ret);
        request.impl().setResponseWare(ware);
    }
}

$PackageWebCoreEnd
