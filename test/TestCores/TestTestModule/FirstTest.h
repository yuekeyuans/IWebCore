#pragma once

#include "core/test/IUnitTestInterface.h"
using namespace IWebCore;

class FirstTest : public IUnitTestInterface<FirstTest, false>
{
    Q_OBJECT
public:
    FirstTest();
};

