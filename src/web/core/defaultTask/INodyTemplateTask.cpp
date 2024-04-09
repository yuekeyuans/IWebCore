#include "INodyTemplateTask.h"
#include "core/config/IProfileImport.h"
#include "core/base/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "web/response/IResponseManage.h"
#include "nody/INodyManage.h"
#include "nody/INodyRenderer.h"

$PackageWebCoreBegin

INodyTemplateTask::INodyTemplateTask()
{
}

void INodyTemplateTask::task()
{
    $Bool nodyEnabled{"http.templates.nody.enabled"};
    if(!nodyEnabled){
        return;
    }

    m_template = new INodyRenderer;
    delete IResponseManage::instance()->getTemplateRenderer();
    IResponseManage::instance()->setTemplateRenderer(m_template);

    if(!m_templateDir.value().isEmpty() && QFileInfo(m_templateDir).exists() && QFileInfo(m_templateDir).isDir()){
        travelFolder(m_templateDir, m_templateDir);
    }
}

void INodyTemplateTask::travelFolder(const QString &path, const QString& root)
{
    QDir dir(path);
    auto entries = dir.entryInfoList();
    for(auto entry : entries){
        if(entry.isDir()){
            travelFolder(entry.absoluteFilePath(), root);
            continue;
        }

        auto fileName = entry.absoluteFilePath();
        if(fileName.endsWith(m_suffix)){
            auto node = INodyManage::instance()->parseContent(IFileUtil::readFileAsString(fileName));
            if(node){
                auto realPath = fileName.replace(root, "");
                m_template->addNody(realPath, node);
            }
        }
    }
}

$PackageWebCoreEnd
