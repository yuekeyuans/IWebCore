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
    $QString folder{"http.fileService.nodyTemplateFolder"};
    if(!folder.value().isEmpty()){
        travelFolder(folder);
    }
}

void INodyTemplateTask::travelFolder(const QString &path)
{
    static $QString folder{"http.fileService.nodyTemplateFolder"};
    QDir dir(path);
    auto entries = dir.entryInfoList();
    for(auto entry : entries){
        if(entry.isDir()){
            travelFolder(entry.absoluteFilePath());
        }else{
            auto fileName = entry.absoluteFilePath();
            if(fileName.endsWith(SUFFIX)){
                auto node = NodyParser().parseContent(IFileUtil::readFileAsString(fileName));
                if(node){
                    auto realPath = fileName.replace(folder, "");
                    IResponseManage::instance()->registerNodyProcesser(realPath, node);
                }
            }
        }
    }
}

$PackageWebCoreEnd
