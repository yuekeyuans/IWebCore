#pragma once

#include "core/base/IHeaderUtil.h"
#include <chrono>

$PackageWebCoreBegin

class TicTac
{
public:
    TicTac(const char* file, const char* function, int line);
    ~TicTac();

private:
    std::chrono::high_resolution_clock::time_point tic;
    QString file;
    QString function;
    QString line;
};

$PackageWebCoreEnd

#define $TIC_TAC  \
    TicTac time_tic_tac##__LINE (__FILE__, __FUNCTION__, __LINE__);

#define $TIC \
    auto timeTic = std::chrono::high_resolution_clock().now();

#define $TAC \
    do{ \
        auto timeTac = std::chrono::high_resolution_clock().now();  \
        auto timeTip = QString("ms in %1 file, %2 line, %3 function,").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);    \
        qDebug().noquote() << std::chrono::duration_cast<std::chrono::microseconds>(timeTac - timeTic).count() * 1.0 / 1000  << timeTip;  \
    }while(0);

#ifdef $UseInLineMode
    #include "ITicTacUtil.cpp"
#endif
