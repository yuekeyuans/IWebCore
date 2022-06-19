#pragma once

#include "IAssetInfo.h"
#include "IAstPreProcessor.h"
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAssetInterface
{
    Q_GADGET
protected:
    IAssetInterface() = default;
public:
    void load(const QString& klassName);
    virtual QString loadFromJsonString();
    virtual void loadFromFunction(); // TODO: 名字有点俗气

    void fatal(const QString& name);
    void fatal(const QString& name, const IAssetInfo& info);

    void warn(const QString& name);
    void warn(const QString& name, const IAssetInfo& info);

    void debug(const QString& name);
    void debug(const QString& name, const IAssetInfo& info);

protected:
    void addFatal(const QString& tag, const QString& info="", const QString& solution="");
    void addWarn(const QString& tag, const QString& info="", const QString& solution="");
    void addDebug(const QString& tag, const QString& info="", const QString& solution="");

private:
    QMap<QString, QPair<QString, QString>> m_fatal;
    QMap<QString, QPair<QString, QString>> m_warn;
    QMap<QString, QPair<QString, QString>> m_debug;
};

$PackageWebCoreEnd
