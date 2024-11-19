#pragma once

#include <IWeb/IHttpControllerInterface>
#include <http/response/IHtmlResponse.h>
#include <http/response/IInvalidResponse.h>
#include <http/response/IStatusResponse.h>

class InvalidController : public IHttpControllerInterface<InvalidController>
{
    Q_GADGET
public:
    InvalidController() = default;

    $GetMapping(testInvalid)
    QString testInvalid(IRequest& request);
};

