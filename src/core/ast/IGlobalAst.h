#pragma once

#include "IAstInterface.h"
#include "IAstPreProcessor.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAst : public IAstInterface
{
    Q_GADGET
    $AsAst(IGlobalAst)
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
    IGlobalAst() = default;
    void fatal(Type type);
    void fatal(Type type, const IAstInfo& info);
    void fatal(Type type, const QString& reason);

    void fatal(const QString& name);
    void fatal(const QString& name, const IAstInfo& info);
    void fatal(const QString& name, const QString& reason);

public:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
