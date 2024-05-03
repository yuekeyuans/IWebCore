#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $EnableBeanResolveStrictMode(boolValue) \
    PP_NORMAL_CONTEXT_CONFIG(EnableBeanResolveStrictMode, BEAN_RESOLVE_IS_STRICT_MODE, boolValue)

#define $EnableSqlInfoPrint(boolValue) \
    PP_NORMAL_CONTEXT_CONFIG(EnableSqlInfoPrint, ENABLE_SQL_PRINT_INFO, boolValue)
