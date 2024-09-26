#pragma once

#include "core/task/default/IInitializationTaskInterface.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

class INodyRenderer;
class INodyTemplateTask : public IInitializationTaskInterface<INodyTemplateTask>
{
public:
    INodyTemplateTask();

public:
    virtual void task() final;

private:
    void travelFolder(const QString& path, const QString& root);

private:
    $QString m_suffix{"/http/templates/nody/suffix"};
    $QString m_templateDir{"/http/templates/nody/templateDir"};
    INodyRenderer* m_template{};
};

$PackageWebCoreEnd
