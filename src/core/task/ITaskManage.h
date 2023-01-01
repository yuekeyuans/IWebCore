#pragma once

/**
 * @brief The  class
 *
 * 曾用名：
 * IFunPostInvokeManage
 * IDeferInvokeManage
 * ITaskManage
 *
 * 用于调用 函数使用
 *
 */
#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"

$PackageWebCoreBegin

class IMiddleWare;

class ITaskManage
{
    $UseInstance(ITaskManage)
public:
    using FunType = std::function<void()>;
    using ArgumentTaskFunType = std::function<void(const QStringList&)>;

private:
    ITaskManage() = default;

public:
    static void run();
    static void run(int argc, char** argv);
    static void run(const QStringList& arguments);

    static void registerArgumentTask(ArgumentTaskFunType fun);
    static void registerConfigrator(FunType fun);
    static void registerInitializer(FunType fun);
    static void registerController(FunType fun);
    static void registerMiddleWare(FunType fun);
    static void registerSessionInterface(FunType fun);

    static void registerFirstInvoker(FunType fun);
    static void registerLastInvoker(FunType fun);

    // 打印 信息
    static void registerBluePrint(FunType fun);

    // 立即调用的 异步函数
    static void registerAsyncTask(FunType fun);

private:
    static void invokeArgumentTasks(const QStringList&);
    static void invokeConfigers();
    static void invokeInitializers();
    static void invokeControllers();
    static void invokeMiddleWares();


    static void invokeFirstInvokers();
    static void invokeLastInvokers();

    static void invokeBluePrint();
    static void invokeSessions();
private:
    QList<ArgumentTaskFunType> m_ArgumentTasks;
    QList<FunType> m_configurators;
    QList<FunType> m_initializers;
    QList<FunType> m_controllers;
    QList<FunType> m_middleWares;
    QList<FunType> m_blueprints;
    QList<FunType> m_sessions;      // NOTE: 理论上这只有一个的

    QList<FunType> m_firstInvokers;
    QList<FunType> m_lastInvokers;

    bool m_isStarted{ false };
};

$PackageWebCoreEnd
