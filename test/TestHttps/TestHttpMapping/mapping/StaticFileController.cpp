#include "StaticFileController.h"
#include "core/application/IApplication.h"

StaticFileController::StaticFileController()
{

}

IFileResponse StaticFileController::getFile1()
{
    auto path = IApplication::applicationDirPath();
    return path + "/TestHttpMapping.exe";
}

IFileResponse StaticFileController::getFile2()
{
    QString path = __FILE__;
    auto file = QFileInfo(path).absolutePath() + "/demoImage.png";
    return file;
}

IFileResponse StaticFileController::getFile3()
{
    return "TestHttpMapping.exe"_file;
}

IFileResponse StaticFileController::getFile4()
{
    auto path = IApplication::applicationDirPath() + "/TestHttpMapping.exe";
    IFileResponse response(path);
    response.enableContentDisposition();
    return response;
}

void StaticFileController::getFile5(IResponse &response)
{
    auto path = IApplication::applicationDirPath() + "/TestHttpMapping.exe";
    IFileResponse fileResponse(path);
    response.setContent(fileResponse);
}

IFileResponse StaticFileController::getConfigFile()
{
    return "config.json";
}
