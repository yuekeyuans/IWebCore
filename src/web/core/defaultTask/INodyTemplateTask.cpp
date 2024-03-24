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
    $QString directory{"http.fileService.nodyTemplateDirectory"};
    if(!directory.isFound()){
        qDebug() << "directory not set";
    }
    travelDirectory(directory);
}

void INodyTemplateTask::travelDirectory(const QString &path)
{
    static $QString directory{"http.fileService.nodyTemplateDirectory"};
    QDir dir(path);
    auto entries = dir.entryInfoList();
    for(auto entry : entries){
        if(entry.isDir()){
            travelDirectory(entry.absoluteFilePath());
        }else{
            auto fileName = entry.absoluteFilePath();
            if(fileName.endsWith(SUFFIX)){
                auto node = NodyParser().parseContent(IFileUtil::readFileAsString(fileName));
                if(node){
                    auto realPath = fileName.replace(directory, "");
                    IResponseManage::instance()->registerNodyProcesser(realPath, node);
                }
            }
        }
    }
}

$PackageWebCoreEnd
