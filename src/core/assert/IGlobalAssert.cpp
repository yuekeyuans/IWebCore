#include "IGlobalAssert.h"

$PackageWebCoreBegin

void IGlobalAssert::fatal(IGlobalAssert::Type type)
{
    QString name = QMetaEnum::fromType<IGlobalAssert::Type>().valueToKey(type);
    this->IAssertInterface::fatal(name);
}

void IGlobalAssert::fatal(IGlobalAssert::Type type, const IAssertInfo &info)
{
    QString name = QMetaEnum::fromType<IGlobalAssert::Type>().valueToKey(type);
    this->IAssertInterface::fatal(name, info);
}

void IGlobalAssert::fatal(IGlobalAssert::Type type, const QString &reason)
{
    IAssertInfo info;
    info.reason = reason;
    QString name = QMetaEnum::fromType<IGlobalAssert::Type>().valueToKey(type);
    this->IAssertInterface::fatal(name, info);
}

void IGlobalAssert::fatal(const QString &name)
{
    this->IAssertInterface::fatal(name);
}

void IGlobalAssert::fatal(const QString &name, const IAssertInfo &info)
{
    this->IAssertInterface::fatal(name, info);
}

void IGlobalAssert::fatal(const QString &name, const QString &reason)
{
    IAssertInfo info;
    info.reason = reason;
    this->IAssertInterface::fatal(name, info);
}

void IGlobalAssert::loadFromFunction()
{
    /// global
    addFatal("Assert_Load_Json_Error", "your json format is not correct");
    addFatal("UnImplimentedMethod", "this method is not implimented.");

    /// macro
    addFatal("EnableBluePrintParamError", "");

    /// configuration
    addFatal("ConfigurationMayNotInitialized"
             , "the configuration will complete at the begin of main. "
               "when you use configuration when configuration not complete, "
               "this warning popup."
             , "change your code, or ignore this warning");

    addFatal("ConfigurationMergeJsonValueError");
    addFatal("ConfigurationCovertYamlFailError");
    addFatal("ConfigurationResolveJsonError");

    /// task
    addFatal("TaskDeferRegisterNotAllowed");
    addFatal("TaskShouldNotBeRegistered");
}

$PackageWebCoreEnd
