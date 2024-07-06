#pragma once

#include <core/test/IUnitTestInterface.h>

class IGlobalTest : public IUnitTestInterface<IGlobalTest>
{
    Q_OBJECT
public:
    IGlobalTest();

private slots:
    void slotTest1();
};

