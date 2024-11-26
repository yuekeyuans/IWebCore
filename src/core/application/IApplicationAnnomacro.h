#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $EnableUnitTest(boolValue)   \
    PP_NORMAL_CONTEXT_CONFIG(IHttpUnitTest_EnabledUnitTest, /test/unittest/enabled, boolValue)


#define $EnableTaskOutput(value)    \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableTaskOutput_taskOut, /task/taskOutputEnabled, value)
