#pragma once

#include <IWebCore>

class IMultiPartJarController : public IControllerInterface<IMultiPartJarController, true>
{
    Q_GADGET
    $AsController (IMultiPartJarController, multipart)
public:
    IMultiPartJarController() =default;

    // multipartjar
    $PostMapping (testFileMultiPartJar)
    QString testFileMultiPartJar(IMultiPartJar jar);

    $PostMapping (testFileMultiPartJarNotExist)
    QString testFileMultiPartJarNotExist(IMultiPartJar jar);

    $PostMapping (testFileMultiPartNames)
    QString testFileMultiPartNames(IMultiPartJar jar);

    // multipart
    $PostMapping (testFileMultiPart)
    QString testFileMultiPart(IMultiPart file_1);
};

