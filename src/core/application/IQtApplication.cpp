#include "IQtApplication.h"

#include "core/task/ITaskManage.h"

$PackageWebCoreBegin

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
