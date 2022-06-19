#pragma once

#include "IAssetInterface.h"
#include "IAstPreProcessor.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAsset : public IAssetInterface
{
    Q_GADGET
    $AsAsset(IGlobalAsset)
public:
    enum Type{
        UnImplimentedMethod,
        EnableBluePrintParamError,
        ConfigurationMayNotInitialized,
        ConfigurationMergeJsonValueError,
        ConfigurationResolveJsonError,
        ConfigurationCovertYamlFailError,
        TaskDeferRegisterNotAllowed,
    };
    Q_ENUM(Type);
public:
    IGlobalAsset() = default;
    void fatal(Type type);
    void fatal(Type type, const IAssetInfo& info);
    void fatal(Type type, const QString& reason);

    void fatal(const QString& name);
    void fatal(const QString& name, const IAssetInfo& info);
    void fatal(const QString& name, const QString& reason);

public:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
