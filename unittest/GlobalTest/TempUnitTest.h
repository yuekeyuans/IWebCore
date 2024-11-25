#pragma once

#include "core/test/IUnitTestInterface.h"

class TempUnitTest : public IUnitTestInterface<TempUnitTest>
{
    Q_OBJECT
public:
    TempUnitTest()  = default;

private slots:
    void test_IJson();
};

