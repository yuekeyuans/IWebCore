#pragma once

#include "IAssertInterface.h"
#include "IAssertPreProcessor.h"
#include "core/base/IHeaderUtil.h"

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
    Q_ENUM(Type)
public:
    IGlobalAssert() = default;

public:
    using IAssertInterface::fatal;
    void fatal(Type type);
    void fatal(Type type, const IAssertInfo& info);
    void fatal(Type type, const QString& reason);

public:
    virtual void loadAssert() final;
};

$PackageWebCoreEnd

#ifdef $UseInLineMode
    #include "IGlobalAssert.cpp"
#endif
