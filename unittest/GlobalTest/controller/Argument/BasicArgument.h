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
    QString multipart(const IMultiPart& name, const IMultiPart& file){
        qDebug() << file.m_content.toQString();
        return name.m_name.toQString() + ": " + name.m_content.toQString() + ": " + file.m_fileName.toQString();
    }
};

