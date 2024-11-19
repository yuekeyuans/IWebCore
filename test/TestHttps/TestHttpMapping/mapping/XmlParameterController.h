#pragma once

#include <IWeb/IControllerInterface>

class XmlParameterController: public IHttpControllerInterface<XmlParameterController>
{
    Q_GADGET
    $AsController(XmlParameterController)
public:
    XmlParameterController();
};


