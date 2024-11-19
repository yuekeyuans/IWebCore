#pragma once

#include <QtCore>
#include <IWebCore>

class XmlParameterController: public IControllerInterface
{
    Q_GADGET
    $AsController(XmlParameterController)
public:
    XmlParameterController();
};

//$RegisterController(XmlParameterController)

