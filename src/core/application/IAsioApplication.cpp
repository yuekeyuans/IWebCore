#include "IAsioApplication.h"
#ifdef _WIN32
#include <windows.h>
#endif

$PackageWebCoreBegin

namespace detail
{
    class SignalHandler {
    public:
        SignalHandler(asio::io_context& io_context)
            : io_context_(io_context), signals_(io_context) {

    #ifdef _WIN32
            // 在 Windows 上使用控制台处理函数
            SetConsoleCtrlHandler(&SignalHandler::ConsoleCtrlHandler, TRUE);
    #else
            // 在非 Windows 上监听 SIGINT 和 SIGTERM
            signals_.add(SIGINT);
            signals_.add(SIGTERM);
            signals_.async_wait([this](const asio::error_code& error, int signal_number) {
                if (!error) {
                    std::cout << "Signal received: " << signal_number << ". Stopping io_context." << std::endl;
                    handle_stop();
                }
            });
    #endif
        }

        // 停止 io_context
        void handle_stop() {
            io_context_.stop();
        }

    #ifdef _WIN32
        static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType) {
            if (ctrlType == CTRL_C_EVENT) {
                std::cout << "Ctrl+C detected, stopping io_context." << std::endl;
                io_context_ptr_->stop();
                return TRUE;
            }
            return FALSE;
        }

        static void set_io_context(asio::io_context* io_context) {
            io_context_ptr_ = io_context;
        }

    private:
        static asio::io_context* io_context_ptr_;  // 静态指针
    #endif

    private:
        asio::io_context& io_context_;  // 引用 io_context
        asio::signal_set signals_;      // 信号集（非 Windows 上使用）
    };

    #ifdef _WIN32
    asio::io_context* SignalHandler::io_context_ptr_ = nullptr;  // 静态指针初始化
    #endif
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

#ifdef _WIN32
    detail::SignalHandler::set_io_context(m_ioContext);
#endif
    detail::SignalHandler signal_handler(*m_ioContext);

    m_ioContext->run();
    return 0;
}

$PackageWebCoreEnd
