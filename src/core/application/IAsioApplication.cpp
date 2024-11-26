#include "IAsioApplication.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

$PackageWebCoreBegin

namespace detail
{
class SignalHandler
{
public:
    SignalHandler(asio::io_context* io_context);

    static asio::io_context* io_context_ptr_;
private:
    asio::signal_set signals_;
};

asio::io_context* SignalHandler::io_context_ptr_ = nullptr;

#ifdef _WIN32
static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType) {
    if (ctrlType == CTRL_C_EVENT) {
        std::cout << "Ctrl+C detected, stopping io_context." << std::endl;
        SignalHandler::io_context_ptr_->stop();
        return TRUE;
    }
    return FALSE;
}
#endif

SignalHandler::SignalHandler(asio::io_context *io_context) : signals_(*io_context)
{
    io_context_ptr_ = io_context;
#ifdef _WIN32
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
#else
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
    signals_.async_wait([this](const asio::error_code& error, int signal_number) {
        if (!error) {
            std::cout << "Signal received: " << signal_number << ". Stopping io_context." << std::endl;
            io_context_ptr_->stop();
            handle_stop();
        }
    });
#endif
}

}

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
    detail::SignalHandler signal_handler(m_ioContext);

    m_ioContext->run();
    return 0;
}

$PackageWebCoreEnd
