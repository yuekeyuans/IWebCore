#pragma once

#include "core/test/IUnitTestInterface.h"
using namespace IWebCore;

class UnitTest : public IUnitTestInterface<UnitTest, true>
{
    Q_OBJECT
public:
    UnitTest();

private slots:
    void slotTest();
};

