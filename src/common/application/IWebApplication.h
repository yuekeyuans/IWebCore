#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IWebApplication : public QCoreApplication
{
public:
    IWebApplication(int argc, char** argv);

    QStringList getArguments() const;

private:
    QStringList m_arguments;
};

$PackageWebCoreEnd
