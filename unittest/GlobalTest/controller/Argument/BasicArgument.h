#pragma once

#include <IHttp/IHttpControllerInterface>

class BasicArgument : public IHttpControllerInterface<BasicArgument>
{
    Q_GADGET
    $AsController(BasicArgument)
public:
    BasicArgument();

public:
    $GetMapping(irequest)
    QString irequest(IRequest& req){
        return req.url().m_stringView.toQString();
    }
};

