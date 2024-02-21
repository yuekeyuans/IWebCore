#pragma once

#include "core/config/IConfigPreProcessor.h"

#define $EnableConfigFile(fileName) \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableFileClass, PP_FILE, fileName)

#define $EnableDefaultStaticDir(prefix) \
    PP_NORMAL_CONTEXT_CONFIG(EnableDefaultStaticFilePrefix, PP_DEFAULT_STATIC_DIR, prefix)

#define $EnableBluePrint(boolValue) \
    PP_PRIVILIGE_CONTEXT_CONFIG(EnableBluePrint, SYSTEM_BLUE_PRINT, boolValue)

#define $EnableBeanResolveStrictMode(boolValue) \
    PP_NORMAL_CONTEXT_CONFIG(EnableBeanResolveStrictMode, BEAN_RESOLVE_IS_STRICT_MODE, boolValue)

#define $EnableSqlInfoPrint(boolValue) \
    PP_NORMAL_CONTEXT_CONFIG(EnableSqlInfoPrint, ENABLE_SQL_PRINT_INFO, boolValue)
