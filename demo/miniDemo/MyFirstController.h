#pragma once

#include <IWebCore>

class MyFirstController : public IControllerInterface<MyFirstController>
{
    Q_GADGET
    $AsController(MyFirstController)
public:

    $GetMapping(index, /)
    QString index()
    {
        return "hello world";
    }
};
