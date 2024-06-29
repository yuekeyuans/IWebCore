#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/application/IApplicationInterface.h"
#include "core/task/ITaskManage.h"
#include "asio/io_context.hpp"


$PackageWebCoreBegin

class IAsioApplication : public IApplicationInterface
{
public:
    IAsioApplication(int argc, char** argv);

public:
    asio::io_context& ioContext();

public:
    virtual int run() final;

private:
    asio::io_context* m_ioContext{};
};

using IApplication = IAsioApplication;

$PackageWebCoreEnd
