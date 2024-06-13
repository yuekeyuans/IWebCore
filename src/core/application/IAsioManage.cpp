#include "IAsioManage.h"
#include "asio/io_context.hpp"

$PackageWebCoreBegin

IAsioManage::IAsioManage()
{

}

asio::io_context *IAsioManage::getMainIoContext()
{
    return nullptr;
}

$PackageWebCoreEnd
