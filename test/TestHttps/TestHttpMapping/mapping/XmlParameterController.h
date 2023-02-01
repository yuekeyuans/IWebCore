#pragma once

#include <IControllerInterface>

class XmlParameterController: public IControllerInterface<XmlParameterController>
{
    Q_GADGET
    $AsController(XmlParameterController)
public:
    XmlParameterController();
};


