#pragma once

#include <IWeb/IHttpControllerInterface>
#include "http/response/IHtmlResponse.h"
#include "http/response/IStatusResponse.h"

class StatusController : public IHttpControllerInterface<StatusController>
{
    Q_GADGET
public:
    StatusController() = default;

    $GetMapping(statusResponseInt, /int)
    IStatusResponse statusResponseInt();

    $GetMapping(statusResponseIntString, /intString)
    IStatusResponse statusResponseIntString();

    $GetMapping(statusResponseStatus, /status)
    IStatusResponse statusResponseStatus();

    $GetMapping(statusResponseStatusString, /statusString)
    IStatusResponse statusResponseStatusString();

    $GetMapping(userLiteral, /userLiteral)
    IStatusResponse userLiteral();

    $GetMapping(replace)
    IHtmlResponse replace();
};

