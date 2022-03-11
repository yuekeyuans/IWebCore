#include "IHttpSocketManage.h"
#include "IHttpRunner.h"
#include "base/IMetaUtil.h"
#include "base/ISocketUtil.h"
#include "base/ITicTacUtil.h"
#include "common/net/IResponse.h"
#include "common/net/IRequest.h"
#include "common/net/impl/IReqRespRaw.h"
#include "IHttpProcesser.h"
#include "controller/IControllerManage.h"
#include "support/IRequestErrorPreIntercept.h"

$PackageWebCoreBegin

void IHttpSocketManage::addSocket(qintptr handle)
{
    auto runable = new IHttpProcesser(handle);
    instance()->pool.start(runable);
}

bool IHttpSocketManage::interceptStatusCode(IRequest &request, IResponse &response)
{
    auto function = IControllerManage::getStatusFunction(response.status());
    if(function != nullptr){
        IHttpRunner::runStatusFunction(request, response, function);
    }
    return false;
}

$PackageWebCoreEnd

