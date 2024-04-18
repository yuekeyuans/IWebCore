#pragma once

#include "web/core/test/IHttpTestInterface.h"
using namespace IWebCore;

class ControllerTest : public IHttpTestInterface<ControllerTest, true>
{
    Q_OBJECT
public:
    ControllerTest();

    Q_INVOKABLE void a(){}
};

