#pragma once

#include "IConfigurationManage.h"
#include "core/base/IToeUtil.h"
#include "core/base/IPreProcessorUtil.h"

#include <iostream>

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
static const klassName* system_setting_ ## klassName ## _instance = klassName::instance();
