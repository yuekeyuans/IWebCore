#include "IAsioApplication.h"

$PackageWebCoreBegin

IAsioApplication::IAsioApplication(int argc, char **argv)
    :IApplicationInterface(argc, argv)
{
    m_instance = this;
    m_ioContext = new asio::io_context(1);
    ITaskManage::run();
}

asio::io_context &IAsioApplication::ioContext()
{
    return *m_ioContext;
}

int IAsioApplication::run()
{
    m_ioContext->run();
    return 0;
}

$PackageWebCoreEnd
