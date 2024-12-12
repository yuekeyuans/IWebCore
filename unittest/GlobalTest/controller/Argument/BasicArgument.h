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
        return req.url().toQString();
    }

    $PostMapping(multipart)
    QString multipart(const IMultiPart& name){
        return name.name.toQString() + name.content.toQString();
    }
};

