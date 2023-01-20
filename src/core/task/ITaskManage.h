#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"
#include "core/task/ITaskCatagory.h"
#include "core/task/ITaskNode.h"

$PackageWebCoreBegin

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

    void addTaskNode(const ITaskNode& node);

private:
    void execTaskCatagories();
    void execTaskNodes();

private:
    QList<ITaskNode> m_taskNodes;
    QList<ITaskCatagory> m_catagories;
    bool m_isTaskFinished{false};
    QStringList m_arguments;
};

$PackageWebCoreEnd
