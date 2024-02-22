#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $EnableControllerPrint(boolValue) \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableControllerPrint, SYSTEM_CONTROLLER_PRINT, boolValue)
