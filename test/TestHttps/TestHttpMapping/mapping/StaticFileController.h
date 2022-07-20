#pragma once

#include "IWebCore"

class StaticFileController : public IControllerInterface<StaticFileController>
{
    Q_GADGET
    $AsController(StaticFileController, staticFile)
public:
    StaticFileController();

    $GetMapping(getFile1, getFile1)
    IStaticFileResponse getFile1();


    $GetMapping(getFile2, getFile2)
    IStaticFileResponse getFile2();

    $GetMapping(getFile3, getFile3)
    IStaticFileResponse getFile3();

    $GetMapping(getFile4, getFile4)
    IStaticFileResponse getFile4();

    $GetMapping(getFile5, getFile5)
    void getFile5(IResponse& response);

};

