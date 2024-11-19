#pragma once

#include "base/IPreProcessorUtil.h"
#include <core/test/ITestInterface.h>
#include <core/test/ITestPreProcessor.h>

using namespace IWebCore;

class TestCase : public ITestInterface<TestCase>
{
    Q_OBJECT
    $AsTest(TestCase)
public:
    TestCase();
};
