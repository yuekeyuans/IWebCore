#pragma once

#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IApplicationPrivate;
class IApplication : public QCoreApplication
{
    $UseDataPtr(IApplication)
    Q_DISABLE_COPY_MOVE(IApplication)
    Q_CREATE_ON_STACK_ONLY
public:
    IApplication();
    explicit IApplication(int argc, char** argv);
    static IApplication* theInstance();
    static QStringList arguments();
};

#define iApp IApplication::theInstance();

$PackageWebCoreEnd
