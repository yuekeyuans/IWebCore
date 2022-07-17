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
};

