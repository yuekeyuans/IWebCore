#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IApplicationPrivate;
class IApplication : public QCoreApplication
{
    $UseDataPtr(IApplication)
    Q_DISABLE_COPY_MOVE(IApplication);
    Q_CREATE_ON_STACK_ONLY
public:
    IApplication(int argc, char** argv);
    static IApplication* theInstance();
};

#define iApp IApplication::theInstance();

$PackageWebCoreEnd
