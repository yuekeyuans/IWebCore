#pragma once

#include <IWeb/IControllerInterface>

class XmlParameterController: public IControllerInterface<XmlParameterController>
{
    Q_GADGET
    $AsController(XmlParameterController)
public:
    XmlParameterController();
};


