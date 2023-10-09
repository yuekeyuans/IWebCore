#pragma once

#include "core/base/IPreProcessorUtil.h"
#include "core/base/IToeUtil.h"
//#include "core/context/IContextWritter.h"
#include "core/context/IContextManage.h"

#define $AsContext(klassName)   \
    $UseInstance(klassName)

#define PP_SYSTEM_CONTEXT_SETTING(klassName, path, value)   \
class klassName \
{   \
public: \
    klassName(){    \
        QString key = IToeUtil::trimQuote( #path ); \
        QJsonValue obj = QJsonValue(value); \
        IContextManage::addConfig(obj, IContextManage::SystemContextGroup, key); \
    }   \
    static klassName* instance(){   \
        static klassName inst;  \
        return &inst;   \
    }   \
};  \
static const klassName* system_setting_ ## klassName ## _instance = klassName::instance();
