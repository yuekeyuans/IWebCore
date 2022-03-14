#pragma once

#include <IWebCore>

class TestController : public IControllerInterface<TestController>
{
    Q_GADGET
    $AsController(TestController)
public:
    TestController();

    $GetMapping(index, /)
    QString index();

    $GetMapping(cookie, /cookie)
    QString cookie(ICookie& cookie);

    $GetMapping(json, /<name:short>/abc)
    IJsonResponse json($Url(short, name));
};

