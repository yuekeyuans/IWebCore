#pragma once

#include "IConfigurationManage.h"
#include "base/IHeaderUtil.h"
#include "base/IToeUtil.h"
#include "base/IPreProcessorUtil.h"

#define PP_SYSTEM_SETTING(klassName, path, value)   \
class klassName \
{   \
public: \
    klassName(){    \
        QString key = IToeUtil::trimQuote( #path ); \
        QJsonValue val = QJsonValue(value); \
        IConfigurationManage::setSystemValue(key, val); \
    }   \
    static klassName* instance(){   \
        static klassName inst;  \
        return &inst;   \
    }   \
};  \
static klassName* system_setting_ ## klassName ## _instance = klassName::instance();

#define $EnableConfigFile(fileName) \
    PP_SYSTEM_SETTING(EnableFileClass, PP_FILE, fileName)

#define $EnableDefaultStaticDir(prefix) \
    PP_SYSTEM_SETTING(EnableDefaultStaticFilePrefix, PP_DEFAULT_STATIC_DIR, prefix)

#define $EnableBluePrint(boolValue) \
    PP_SYSTEM_SETTING(EnableBluePrint, SYSTEM_BLUE_PRINT, boolValue)

#define $EnableBeanResolveStrictMode(boolValue) \
    PP_SYSTEM_SETTING(EnableBeanResolveStrictMode, BEAN_RESOLVE_IS_STRICT_MODE, boolValue)

#define $EnableSqlInfoPrint(boolValue) \
    PP_SYSTEM_SETTING(EnableSqlInfoPrint, ENABLE_SQL_PRINT_INFO, boolValue)

#define $EnableCatagory(catagoryName) \
    PP_SYSTEM_SETTING(EnableCatagory_##catagoryName, CATAGORY_ENABLE_STATE_##catagoryName, true)

#define $DisableCatagory(catagoryName) \
    PP_SYSTEM_SETTING(DisableCatagory_##catagoryName, CATAGORY_ENABLE_STATE_##catagoryName, false)

#define $EnableTask(catagoryName, taskName) \
    PP_SYSTEM_SETTING(EnableTask_##catagoryName##_##taskName, TASK_ENABLE_STATE_##catagoryName##_##taskName, false)

#define $DisableTask(catagoryName, taskName) \
    PP_SYSTEM_SETTING(DisableTask_##catagoryName##_##taskName, TASK_ENABLE_STATE_##catagoryName##_##taskName, false)


