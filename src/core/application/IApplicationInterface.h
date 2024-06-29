#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IApplicationInterface
{
public:
    IApplicationInterface(int arg, char** argv);
    virtual ~IApplicationInterface() = default;

public:
    static IApplicationInterface* instance();
    QStringList arguments();
    virtual int run() = 0;

protected:
    QStringList m_arguments;
    static IApplicationInterface* m_instance;
};

$PackageWebCoreEnd
