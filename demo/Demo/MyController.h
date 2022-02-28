#pragma once

#include <IWebCore>

class MyController : public IControllerInterface<MyController>
{
    Q_GADGET
    $AsController(MyController)
public:
    MyController() = default;

    $GetMapping(index, /)
    QString index();

    $IgnoreParamWarn(hello)
    $GetMapping(hello, /<name>)
    QString hello(QString name);
};

