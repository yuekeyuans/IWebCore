#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $EnableControllerPrint(boolValue) \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableControllerPrint, SYSTEM_CONTROLLER_PRINT, boolValue)

#define $SetIpAddress(value)    \
    PP_PROFILE_CONFIG(SetIpAddress, http.ip, value)

#define $SetIpPort(value)   \
    PP_PROFILE_CONFIG(SetIpPort, http.port, value)

#define $SetStaticLocation(value)  \
    PP_PROFILE_CONFIG(SetStaticLocation, http.staticLocation, value)
