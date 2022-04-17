#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IWebApplication : public QCoreApplication
{
public:
    IWebApplication(int argc, char** argv);

private:
    const QStringList& getArguments();

private:
    QStringList m_arguments;
};

$PackageWebCoreEnd
