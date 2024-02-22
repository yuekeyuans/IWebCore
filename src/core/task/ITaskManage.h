#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

class ITaskWare;
class ITaskCatagory;

class ITaskManage : public ISingletonUnit<ITaskManage>
{
public:
    using FunType = std::function<void()>;
    using ArgumentTaskFunType = std::function<void(const QStringList&)>;

public:
    static void run();

    void addTaskWare(ITaskWare* node);
    void addTaskCatagory(ITaskCatagory*);

private:
    void invokeTaskCatagories();

private:
    void checkCatagoryExceed();
    void checkTaskExceed();
    void mergetTasksToCatagores();
    void execEachCatagory();

private:
    QList<ITaskWare*> m_taskWares;
    QList<ITaskCatagory*> m_catagories;
    bool m_isTaskFinished{false};
};

$PackageWebCoreEnd
