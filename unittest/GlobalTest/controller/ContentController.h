#pragma once

#include "IHttp/IHttpControllerInterface"


class ContentController : public IHttpControllerInterface<ContentController>
{
    Q_GADGET
    $AsController(Content)
public:
    ContentController();

    $PostMapping(chunkedData)
    QString chunkedData(IString $Body(data)){
        qDebug() << data.toQString();
        return data.toQString();
    }

    $GetMapping(headMethod)
    QString headMethod(){
        return "headMethod";
    }
};

