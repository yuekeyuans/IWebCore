#pragma once

#include <QtCore>
#include <IWebCore>

class XmlParameterController: public IControllerInterface<XmlParameterController>
{
    Q_GADGET
    $AsController(XmlParameterController)
public:
    XmlParameterController();
};


