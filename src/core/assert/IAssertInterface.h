#pragma once

#include "IAssertInfo.h"
#include "IAssertPreProcessor.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAssertInterface
{
    Q_GADGET
protected:
    IAssertInterface() = default;

public:
    void fatal(const QString& name);
    void fatal(const QString& name, const IAssertInfo& info);

    void warn(const QString& name);
    void warn(const QString& name, const IAssertInfo& info);

    void debug(const QString& name);
    void debug(const QString& name, const IAssertInfo& info);

protected:
    virtual void loadAssert() = 0;
    void addFatal(const QString& tag, const QString& info="", const QString& solution="");
    void addWarn(const QString& tag, const QString& info="", const QString& solution="");
    void addDebug(const QString& tag, const QString& info="", const QString& solution="");

private:
    QMap<QString, QPair<QString, QString>> m_fatal;
    QMap<QString, QPair<QString, QString>> m_warn;
    QMap<QString, QPair<QString, QString>> m_debug;
};

$PackageWebCoreEnd

#include "IAssertInterface.cpp"
