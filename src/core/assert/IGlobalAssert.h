#pragma once

#include "IAssertInterface.h"
#include "IAssertPreProcessor.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAssert : public IAssertInterface
{
    Q_GADGET
    $AsAssert(IGlobalAssert)
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
    IGlobalAssert() = default;
    void fatal(Type type);
    void fatal(Type type, const IAssertInfo& info);
    void fatal(Type type, const QString& reason);

    void fatal(const QString& name);
    void fatal(const QString& name, const IAssertInfo& info);
    void fatal(const QString& name, const QString& reason);

public:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
