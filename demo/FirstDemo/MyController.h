#pragma once

#include <IWebCore>
#include "UserTable.h"

class MyController : public IControllerInterface<MyController>
{
public:
    MyController() = default;

    $GetMapping(fun1, /fun1)
    QString fun1();

    $GetMapping(fun2, /fun2)
    QString fun2();

    $GetMapping(fun3, /fun3)
    IJsonResponse fun3($Param(UserTable, userTable));

    $GetMapping(fun4, /fun5)
    IJsonResponse fun4();

    $GetMapping(fun5, /fun5)
    IJsonResponse fun5();

    $GetMapping(fun6, /fun6)
    void fun6(IRequest& request, IResponse& response);
};

