#include "INodyTemplateTask.h"
#include "core/config/IProfileImport.h"
#include "core/util/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "http/response/IResponseManage.h"
#include "http/nody/INodyManage.h"
#include "http/nody/INodyRenderer.h"

$PackageWebCoreBegin

INodyTemplateTask::INodyTemplateTask()
{
}

void INodyTemplateTask::$task()
{
    $Bool nodyEnabled{"/http/templates/nody/enabled", false};
    if(! nodyEnabled.value()){
        return;
    }

    m_template = new INodyRenderer;
    delete IResponseManage::instance()->getTemplateRenderer();
    IResponseManage::instance()->setTemplateRenderer(m_template);

    if(!m_templateDir.value().isEmpty() && QFileInfo(m_templateDir.value()).exists() && QFileInfo(m_templateDir.value()).isDir()){
        travelFolder(*m_templateDir, *m_templateDir);
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
        if(fileName.endsWith(*m_suffix)){
            auto value = IFileUtil::readFileAsString(fileName);
            if(!value){
                qFatal("file read failed");
            }
            auto node = INodyManage::instance()->parseContent(*value);
            if(node){
                auto realPath = fileName.replace(root, "");
                m_template->addNody(realPath, node);
            }
        }
    }
}

$PackageWebCoreEnd
