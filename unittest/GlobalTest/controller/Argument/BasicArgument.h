#pragma once

#include <IHttp/IHttpControllerInterface>
#include "http/net/ICookiePart.h"

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
    QString multipart(const IMultiPart& name, const IMultiPart& file){
        Q_UNUSED(name)
        return file.m_content.toQString();
    }

    $GetMapping(cookiePart)
    QString cookiePart(ICookiePart name){
        return name.m_value.toQString();
    }

    $GetMapping(headerType)
    QString headerType(IString $Header(MyHeader));

    $GetMapping(headerTypeInt)
    QString headerTypeInt(int $Header(MyInt));

    $PostMapping(bodyType)
    QString bodyType(QString $Body(body)){
        return body;
    }
};

