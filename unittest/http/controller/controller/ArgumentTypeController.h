#pragma once

#include <IHttp/IHttpControllerInterface>

class ArgumentTypeController : public IHttpControllerInterface<ArgumentTypeController>
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
    QString irequest(IRequest){ return "hello world";}
};

