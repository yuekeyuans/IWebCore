#pragma once

#include "core/base/IPreProcessorUtil.h"
#include "core/base/IToeUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/task/unit/ITaskInstantUnit.h"

#define $AsConfig(klassName)   \
    $UseInstance(klassName)

#define $AsProfile(klassName)   \
    $UseInstance(klassName)

#define $AsContext(klassName)   \
    $UseInstance(klassName)

#define PP_PRIVILIGE_CONTEXT_CONFIG(klassName, path, value)   \
class klassName : public ITaskInstantUnit < klassName, true >  \
{   \
public:     \
    klassName(){};  \
    virtual void task() final {  \
        QString key = IToeUtil::trimQuote( #path ); \
        QJsonValue obj = QJsonValue(value); \
        IContextManage::instance()->addConfig(obj, key); \
    }    \
};

#define PP_NORMAL_CONTEXT_CONFIG(klassName, path, value)   \
class klassName : public IContextTaskInterface < klassName, true >  \
{   \
    $AsContext(klassName)   \
public:     \
    klassName(){};  \
    virtual QJsonValue getContext() final   {  return value; }  \
    virtual QString getPath() const final { return IToeUtil::trimQuote( #path ); }  \
};
