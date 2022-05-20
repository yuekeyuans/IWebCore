#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "web/controller/IStatusControllerInterface.h"
#include "web/controller/pp/IStatusControllerPreProcessor.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
// banned it!!!
class IDefaultStatusController : public IStatusControllerInterface<IDefaultStatusController, false>
{
    Q_GADGET
    $AsStatusController(IDefaultStatusController);
public:

    IDefaultStatusController() = default;

    $StatusMapping(handle404Page, 404)
    void handle404Page(IRequest& request, IResponse& response);
};

$PackageWebCoreEnd
