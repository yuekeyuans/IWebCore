#pragma once

#include <IWeb/IControllerInterface>

class HttpMethodController : public IControllerInterface<HttpMethodController>
{
    Q_GADGET
    $AsController(controller)
public:
    HttpMethodController();

    $GetMapping(testGet, fun)
    IPlainTextResponse testGet();

    $PutMapping(testPut, fun)
    IPlainTextResponse testPut();

};
