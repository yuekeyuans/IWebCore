#include <Windows.h>
#include <DbgHelp.h>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <fstream>
#include <Psapi.h> // 头文件，包含 EnumProcessModules
#pragma comment(lib, "Psapi.lib") // 链接库

class CrashHandler {
public:
    static void Initialize() {
        // 设置未处理异常的过滤器
        SetUnhandledExceptionFilter(UnhandledExceptionFilter);
    }

private:
    static LONG WINAPI UnhandledExceptionFilter(EXCEPTION_POINTERS* exceptionInfo) {
        // 生成调用链文本文件路径
        QString txtFile = "D:/stacktrace_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".txt";

        // 打开文本文件写入调用链
        std::ofstream outFile(txtFile.toStdString());
        if (!outFile.is_open()) {
            qDebug() << "Failed to create stack trace file:" << txtFile;
            return EXCEPTION_CONTINUE_SEARCH;
        }

        // 写入崩溃基本信息
        outFile << "Crash Report:\n";
        outFile << "Timestamp: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toStdString() << "\n\n";

        // 写入线程上下文信息
        outFile << "Thread Context:\n";
        WriteContextInfo(outFile, exceptionInfo->ContextRecord);
        outFile << "\n";

        // 写入调用链信息
        outFile << "Call Stack:\n";
        WriteStackTrace(outFile, exceptionInfo->ContextRecord);

        // 写入模块加载信息（可选）
        outFile << "\nLoaded Modules:\n";
        WriteLoadedModules(outFile);

        outFile.close();

        qDebug() << "Crash report successfully written to:" << txtFile;

        // 返回异常处理结果
        return EXCEPTION_EXECUTE_HANDLER;
    }

    static void WriteContextInfo(std::ofstream& outFile, CONTEXT* context) {
#if defined(_M_X64)
        outFile << "RIP: 0x" << std::hex << context->Rip << "\n";
        outFile << "RSP: 0x" << std::hex << context->Rsp << "\n";
        outFile << "RBP: 0x" << std::hex << context->Rbp << "\n";
        outFile << "RAX: 0x" << std::hex << context->Rax << "\n";
        outFile << "RBX: 0x" << std::hex << context->Rbx << "\n";
        outFile << "RCX: 0x" << std::hex << context->Rcx << "\n";
        outFile << "RDX: 0x" << std::hex << context->Rdx << "\n";
        outFile << "RSI: 0x" << std::hex << context->Rsi << "\n";
        outFile << "RDI: 0x" << std::hex << context->Rdi << "\n";
#elif defined(_M_IX86)
        outFile << "EIP: 0x" << std::hex << context->Eip << "\n";
        outFile << "ESP: 0x" << std::hex << context->Esp << "\n";
        outFile << "EBP: 0x" << std::hex << context->Ebp << "\n";
        outFile << "EAX: 0x" << std::hex << context->Eax << "\n";
        outFile << "EBX: 0x" << std::hex << context->Ebx << "\n";
        outFile << "ECX: 0x" << std::hex << context->Ecx << "\n";
        outFile << "EDX: 0x" << std::hex << context->Edx << "\n";
        outFile << "ESI: 0x" << std::hex << context->Esi << "\n";
        outFile << "EDI: 0x" << std::hex << context->Edi << "\n";
#endif
    }

    static void WriteStackTrace(std::ofstream& outFile, CONTEXT* context) {
        HANDLE process = GetCurrentProcess();
        HANDLE thread = GetCurrentThread();

        // 初始化调试帮助库
        SymInitialize(process, nullptr, TRUE);

        // 设置堆栈帧
        STACKFRAME64 stackFrame;
        memset(&stackFrame, 0, sizeof(STACKFRAME64));

        DWORD machineType = 0;
#if defined(_M_X64)
        machineType = IMAGE_FILE_MACHINE_AMD64;
        stackFrame.AddrPC.Offset = context->Rip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context->Rsp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context->Rsp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#elif defined(_M_IX86)
        machineType = IMAGE_FILE_MACHINE_I386;
        stackFrame.AddrPC.Offset = context->Eip;
        stackFrame.AddrPC.Mode = AddrModeFlat;
        stackFrame.AddrFrame.Offset = context->Ebp;
        stackFrame.AddrFrame.Mode = AddrModeFlat;
        stackFrame.AddrStack.Offset = context->Esp;
        stackFrame.AddrStack.Mode = AddrModeFlat;
#endif

        // 遍历调用堆栈
        while (StackWalk64(
                   machineType, process, thread,
                   &stackFrame, context, nullptr,
                   SymFunctionTableAccess64, SymGetModuleBase64, nullptr)) {
            // 获取函数名和地址
            DWORD64 address = stackFrame.AddrPC.Offset;
            if (address == 0) {
                break;
            }

            char symbolBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)] = {0};
            SYMBOL_INFO* symbol = (SYMBOL_INFO*)symbolBuffer;
            symbol->MaxNameLen = MAX_SYM_NAME;
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

            DWORD64 displacement = 0;
            if (SymFromAddr(process, address, &displacement, symbol)) {
                outFile << "Function: " << symbol->Name
                        << " - Address: 0x" << std::hex << symbol->Address << "\n";
            } else {
                outFile << "Function: [Unknown] - Address: 0x" << std::hex << address << "\n";
            }

            // 获取源文件信息
            IMAGEHLP_LINE64 line;
            DWORD lineDisplacement = 0;
            memset(&line, 0, sizeof(IMAGEHLP_LINE64));
            line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

            if (SymGetLineFromAddr64(process, address, &lineDisplacement, &line)) {
                outFile << "    File: " << line.FileName
                        << " - Line: " << line.LineNumber << "\n";
            }
        }

        // 清理调试帮助库
        SymCleanup(process);
    }

    static void WriteLoadedModules(std::ofstream& outFile) {
        HANDLE process = GetCurrentProcess();
        HMODULE modules[1024];
        DWORD needed;

        if (EnumProcessModules(process, modules, sizeof(modules), &needed)) {
            for (unsigned int i = 0; i < (needed / sizeof(HMODULE)); i++) {
                char moduleName[MAX_PATH];
                if (GetModuleFileNameExA(process, modules[i], moduleName, sizeof(moduleName))) {
                    outFile << moduleName << "\n";
                }
            }
        }
    }
};
