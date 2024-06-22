#pragma once

#include <IHttp/IHttpControllerInterface>

class RequestParameterController : public IHttpControllerInterface<RequestParameterController>
{
    Q_GADGET
public:
    RequestParameterController() = default;

    $GetMapping(fun1, fun1)
    QString fun1($Body(IStringView, data));
};

