#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IApplication : public QCoreApplication
{
public:
    IApplication(int argc, char** argv);

private:
    const QStringList& getArguments();

private:
    QStringList m_arguments;
};

$PackageWebCoreEnd
