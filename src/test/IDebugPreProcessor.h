#pragma once

#include "test/IDebugInterface.h"

#define $UseDebug(klassName)    \
    static klassName s_debug;

#define $Debug \
auto a = []()->IWebCore::IDebugInterface*{  \
    return &s_debug;    \
};
