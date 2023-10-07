#include "IGlobalAssert.h"

$PackageWebCoreBegin

inline void IGlobalAssert::fatal(IGlobalAssert::Type type)
{
    QString name = QMetaEnum::fromType<IGlobalAssert::Type>().valueToKey(type);
    this->IAssertInterface::fatal(name);
}

inline void IGlobalAssert::fatal(IGlobalAssert::Type type, const IAssertInfo &info)
{
    QString name = QMetaEnum::fromType<IGlobalAssert::Type>().valueToKey(type);
    this->IAssertInterface::fatal(name, info);
}

inline void IGlobalAssert::fatal(IGlobalAssert::Type type, const QString &reason)
{
    IAssertInfo info;
    info.reason = reason;
    QString name = QMetaEnum::fromType<IGlobalAssert::Type>().valueToKey(type);
    this->IAssertInterface::fatal(name, info);
}

inline void IGlobalAssert::loadAssert()
{
    // IApplication
    addFatal("IApplication_not_created", "you can not get any IApplication instance when IApplication not created");

    /// global
    addFatal("Assert_Load_Json_Error", "your json format is not correct");
    addFatal("UnImplimentedMethod", "this method is not implimented.");

    /// macro
    addFatal("EnableBluePrintParamError", "");

    /// context
    addFatal("ConfigurationMayNotInitialized"
             , "the configuration will complete at the begin of main. "
               "when you use configuration when configuration not complete, "
               "this warning popup."
             , "change your code, or ignore this warning");

    addFatal("ConfigurationMergeJsonValueError");
    addFatal("ConfigurationCovertYamlFailError");
    addFatal("ConfigurationResolveJsonError");
    addFatal("ContextAddPathInvalid");
    addFatal("ContextRemovePathInvalid", "remove path can not be empty");
    addFatal("ContextResolvePathInvalid", "path can not be resolved to match the context");

    /// task
    addFatal("TaskDeferRegisterNotAllowed");
    addFatal("TaskShouldNotBeRegistered", "task can not be registered when the task run finished");
    addWarn("CatagoryRangeExceed", "catagory range ought to be in 0 and 100");
    addWarn("TaskRangeExceed", "catagory range ought to be in 0 and 100");
    addWarn("TaskWithErrorCatagory", "this task`s catagory does not exist, please check your code");
}

$PackageWebCoreEnd
