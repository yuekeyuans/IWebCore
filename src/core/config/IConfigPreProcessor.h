#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IProfileTaskInterface.h"
#include "core/task/unit/ITaskInstantUnit.h"

#define PP_PRIVILIGE_CONTEXT_CONFIG(klassName, path_, value)   \
$PackageWebCoreBegin  \
class klassName : public ITaskInstantUnit < klassName, true >  \
{   \
public:     \
    klassName() {};  \
    virtual void $task() final {  \
        std::string key = #path_ ; \
        IJson obj = IJson(value); \
        IContextManage::instance()->addConfig(obj, key); \
    }    \
};      \
$PackageWebCoreEnd

#define PP_NORMAL_CONTEXT_CONFIG(klassName, path_, value)   \
$PackageWebCoreBegin    \
class klassName : public IContextTaskInterface < klassName, true >  \
{   \
public:     \
    klassName() {};  \
    virtual IJson config() final   {  return value; }  \
    virtual std::string path() const final { return #path_ ; }  \
};  \
$PackageWebCoreEnd

#define PP_PROFILE_CONFIG(klassName, path_, value) \
$PackageWebCoreBegin    \
class klassName : public IProfileTaskInterface < klassName, true >  \
{   \
public:     \
    klassName() {};  \
    virtual IJson config() final   {  return value; }  \
    virtual std::string path() const final { return #path_ ; }  \
};  \
$PackageWebCoreEnd
