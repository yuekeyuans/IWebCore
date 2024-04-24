#pragma once

#include <IWeb/IHttpController>
#include "http/response/IHtmlResponse.h"
#include "http/response/IStatusResponse.h"

class StatusController : public IHttpControllerInterface<StatusController>
{
    Q_GADGET
public:
    StatusController() = default;

    $GetMapping(statusResponse, /status)
    IStatusResponse statusResponse();
};

