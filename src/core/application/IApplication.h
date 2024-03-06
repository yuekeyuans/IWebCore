#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IStackObjectUnit.h"

$PackageWebCoreBegin

class IApplicationPrivate;
class IApplication : public QCoreApplication, public IStackObjectUnit
{
    $UseDataPtr(IApplication)
public:
    IApplication();
    explicit IApplication(int argc, char** argv);
    ~IApplication();

public:
    static const IApplication* theInstance();
    static const QStringList& arguments();
};

#define iApp IApplication::theInstance();

$PackageWebCoreEnd
