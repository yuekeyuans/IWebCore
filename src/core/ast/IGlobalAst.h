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
    };
    Q_ENUM(Type);
public:
    IGlobalAst() = default;
    void fatal(Type type);
    void fatal(const QString& name);
    void fatal(const QString& name, const IAstInfo& info);

public:
    virtual void loadFromFunction() final;
};

$PackageWebCoreEnd
