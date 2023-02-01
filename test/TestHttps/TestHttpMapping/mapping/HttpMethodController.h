#pragma once

#include <IControllerInterface>

class HttpMethodController : public IControllerInterface<HttpMethodController>
{
    Q_GADGET
    $AsController(HttpMethodController, controller)
private:
    HttpMethodController();

    $GetMapping(testGet, fun)
    IPlainTextResponse testGet();

    $PutMapping(testPut, fun)
    IPlainTextResponse testPut();

};
