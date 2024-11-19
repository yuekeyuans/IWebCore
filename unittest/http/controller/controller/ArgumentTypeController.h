#pragma once

#include <IHttp/IHttpControllerInterface>

class ArgumentTypeController : public IHttpControllerInterface<ArgumentTypeController, false>
{
    Q_GADGET
    $AsController(ArgumentTypeController)
public:
    ArgumentTypeController() = default;

    $GetMapping(emptyRequest)
    QString emptyRequest();

    $GetMapping(irequestRef)
    QString irequestRef(IRequest&);

    $GetMapping(constIRequestRef)
    QString constIRequestRef(const IRequest&);

    $GetMapping(irequest)
    QString irequest(IRequest);

    $GetMapping(iresponseRef)
    QString iresponseRef(IResponse&);
};

