#include "IQtApplication.h"

#include "core/task/ITaskManage.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

IQtApplication::IQtApplication(int argc, char **argv)
    : QCoreApplication(argc, argv), IApplicationInterface(argc, argv)
{
    m_instance = this;
    ITaskManage::run();
}

int IQtApplication::run()
{
    return QCoreApplication::exec();
}

$PackageWebCoreEnd
