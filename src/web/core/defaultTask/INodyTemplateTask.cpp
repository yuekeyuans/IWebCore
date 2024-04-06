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
    delete IResponseManage::instance()->getRenderTemplate();
    IResponseManage::instance()->setRenderTemplate(m_template);

    if(!defaultFolder.value().isEmpty()){
        travelFolder(defaultFolder, defaultFolder);
    }

    if(!folder.value().isEmpty()){
        travelFolder(folder, defaultFolder);
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
        if(fileName.endsWith(suffix)){
            auto node = INodyManage::instance()->parseContent(IFileUtil::readFileAsString(fileName));
            if(node){
                auto realPath = fileName.replace(root, "");
                m_template->addNody(realPath, node);
            }
        }
    }
}

$PackageWebCoreEnd
