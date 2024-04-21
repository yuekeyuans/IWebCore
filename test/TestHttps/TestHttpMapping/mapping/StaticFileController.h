#pragma once

#include <IWeb/IControllerInterface>

class StaticFileController : public IHttpControllerInterface<StaticFileController>
{
    Q_GADGET
    $AsController(staticFile)
public:
    StaticFileController();

    $GetMapping(getFile1, getFile1)
    IFileResponse getFile1();


    $GetMapping(getFile2, getFile2)
    IFileResponse getFile2();

    $GetMapping(getFile3, getFile3)
    IFileResponse getFile3();

    $GetMapping(getFile4, getFile4)
    IFileResponse getFile4();

    $GetMapping(getFile5, getFile5)
    void getFile5(IResponse& response);

    $GetMapping(getConfigFile, getConfigFile)
    IFileResponse getConfigFile();
};

