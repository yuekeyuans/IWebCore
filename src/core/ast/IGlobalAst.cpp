#include "IGlobalAst.h"

$PackageWebCoreBegin

void IGlobalAst::fatal(IGlobalAst::Type type)
{
    QString name = QMetaEnum::fromType<IGlobalAst::Type>().valueToKey(type);
    this->IAstInterface::fatal(name);
}

void IGlobalAst::fatal(IGlobalAst::Type type, const IAstInfo &info)
{
    QString name = QMetaEnum::fromType<IGlobalAst::Type>().valueToKey(type);
    this->IAstInterface::fatal(name, info);
}

void IGlobalAst::fatal(IGlobalAst::Type type, const QString &reason)
{
    IAstInfo info;
    info.reason = reason;
    QString name = QMetaEnum::fromType<IGlobalAst::Type>().valueToKey(type);
    this->IAstInterface::fatal(name, info);
}

void IGlobalAst::fatal(const QString &name)
{
    this->IAstInterface::fatal(name);
}

void IGlobalAst::fatal(const QString &name, const IAstInfo &info)
{
    this->IAstInterface::fatal(name, info);
}

void IGlobalAst::fatal(const QString &name, const QString &reason)
{
    IAstInfo info;
    info.reason = reason;
    this->IAstInterface::fatal(name, info);
}

void IGlobalAst::loadFromFunction()
{
    addFatal("Assert_Load_Json_Error", "your json format is not correct");
    addFatal("UnImplimentedMethod", "this method is not implimented.");
    addFatal("EnableBluePrintParamError", "");
    addFatal("ConfigurationMayNotInitialized"
             , "the configuration will complete at the begin of main. "
               "when you use configuration when configuration not complete, "
               "this warning popup."
             , "change your code, or ignore this warning");

    addFatal("ConfigurationMergeJsonValueError");
    addFatal("ConfigurationCovertYamlFailError");
    addFatal("ConfigurationResolveJsonError");

    addFatal("TaskDeferRegisterNotAllowed");
}

$PackageWebCoreEnd
