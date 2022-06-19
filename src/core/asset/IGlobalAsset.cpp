#include "IGlobalAsset.h"

$PackageWebCoreBegin

void IGlobalAsset::fatal(IGlobalAsset::Type type)
{
    QString name = QMetaEnum::fromType<IGlobalAsset::Type>().valueToKey(type);
    this->IAssetInterface::fatal(name);
}

void IGlobalAsset::fatal(IGlobalAsset::Type type, const IAssetInfo &info)
{
    QString name = QMetaEnum::fromType<IGlobalAsset::Type>().valueToKey(type);
    this->IAssetInterface::fatal(name, info);
}

void IGlobalAsset::fatal(IGlobalAsset::Type type, const QString &reason)
{
    IAssetInfo info;
    info.reason = reason;
    QString name = QMetaEnum::fromType<IGlobalAsset::Type>().valueToKey(type);
    this->IAssetInterface::fatal(name, info);
}

void IGlobalAsset::fatal(const QString &name)
{
    this->IAssetInterface::fatal(name);
}

void IGlobalAsset::fatal(const QString &name, const IAssetInfo &info)
{
    this->IAssetInterface::fatal(name, info);
}

void IGlobalAsset::fatal(const QString &name, const QString &reason)
{
    IAssetInfo info;
    info.reason = reason;
    this->IAssetInterface::fatal(name, info);
}

void IGlobalAsset::loadFromFunction()
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
