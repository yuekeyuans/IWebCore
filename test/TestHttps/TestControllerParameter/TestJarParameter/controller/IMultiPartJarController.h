#pragma once

#include <IWebCore>

class IMultiPartJarController : public IControllerInterface<IMultiPartJarController, true>
{
    Q_GADGET
    $AsController (IMultiPartJarController, multipart)
public:
    IMultiPartJarController() =default;

    $PostMapping (getMultiPartJar)
    QString getMultiPartJar(IMultiPartJar jar);
};

