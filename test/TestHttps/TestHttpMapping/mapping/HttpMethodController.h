#pragma once

#include <IWeb/IControllerInterface>

class HttpMethodController : public IHttpControllerInterface<HttpMethodController>
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
