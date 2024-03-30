#include "INodyTemplateTask.h"
#include "core/config/IProfileImport.h"
#include "core/base/IFileUtil.h"
#include "web/response/IResponseManage.h"
#include "NodyParser.h"

$PackageWebCoreBegin

INodyTemplateTask::INodyTemplateTask()
{

}

void INodyTemplateTask::task()
{
    $QString defaultFolder{"http.templates.nody.defaultTemplateFolder"};
    if(!defaultFolder.value().isEmpty()){
        travelFolder(defaultFolder, defaultFolder);
    }

    $QString folder{"http.templates.nody.templateFolder"};
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
        }else{
            auto fileName = entry.absoluteFilePath();
            if(fileName.endsWith(SUFFIX)){
                auto node = NodyParser().parseContent(IFileUtil::readFileAsString(fileName));
                if(node){
                    auto realPath = fileName.replace(root, "");
                    IResponseManage::instance()->registerNodyProcesser(realPath, node);
                }
            }
        }
    }
}

$PackageWebCoreEnd
