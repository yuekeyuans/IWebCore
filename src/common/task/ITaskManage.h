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
#include "assertion/IAssertPreProcessor.h"
#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"

$PackageWebCoreBegin

class ITaskManage
{
    $UseInstance(ITaskManage)
public:
    using FunType = std::function<void()>;
    using ArgumentParserFunType = std::function<void(const QStringList&)>;

private:
    ITaskManage() = default;

public:
    static void run();
    static void run(int argc, char** argv);
    static void run(const QStringList& arguments);

    static void registerArgumentParser(ArgumentParserFunType fun);
    static void registerConfigrator(FunType fun);
    static void registerInitializer(FunType fun);
    static void registerController(FunType fun);

    // 打印 信息
    static void registerBluePrint(FunType fun);

    // 立即调用的 异步函数
    static void registerAsyncTask(FunType fun);

private:
    static void invokeArgumentParsers(const QStringList&);
    static void invokeControllers();
    static void invokeConfigers();
    static void invokeInitializers();
    static void invokeBluePrint();

private:
    QList<ArgumentParserFunType> m_argumentParsers;
    QList<FunType> m_configurators;
    QList<FunType> m_initializers;
    QList<FunType> m_controllers;

    QList<FunType> m_blueprints;

    bool m_isStarted{ false };
};

$PackageWebCoreEnd
