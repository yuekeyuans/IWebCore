#pragma once

#include "core/task/default/IInitializationTaskInterface.h"

$PackageWebCoreBegin

class INodyTemplateTask : public IInitializationTaskInterface<INodyTemplateTask>
{
public:
    INodyTemplateTask();

public:
    virtual void task() final;

private:
    void travelFolder(const QString& path, const QString& root);

private:
    static constexpr char SUFFIX[] = "yky";
};

$PackageWebCoreEnd
