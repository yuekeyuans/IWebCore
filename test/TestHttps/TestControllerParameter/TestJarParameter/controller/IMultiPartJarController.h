#pragma once

#include <IWebCore>

class IMultiPartJarController : public IControllerInterface<IMultiPartJarController, true>
{
    Q_GADGET
    $AsController (IMultiPartJarController, multipart)
public:
    IMultiPartJarController() =default;

    // multipartjar

    // TODO: 这里有一个待解决的问题， 就是，注册函数名称和注册函数不一致，错误提示不正确
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

