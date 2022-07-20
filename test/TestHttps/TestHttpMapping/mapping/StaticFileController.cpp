#include "StaticFileController.h"

StaticFileController::StaticFileController()
{

}

IStaticFileResponse StaticFileController::getFile1()
{
    auto path = IApplication::applicationDirPath();
    return path + "/TestHttpMapping.exe";
}

IStaticFileResponse StaticFileController::getFile2()
{
    QString path = __FILE__;
    auto file = QFileInfo(path).absolutePath() + "/demoImage.png";
    return file;
}

IStaticFileResponse StaticFileController::getFile3()
{
    return "TestHttpMapping.exe"_file;
}

IStaticFileResponse StaticFileController::getFile4()
{
    auto path = IApplication::applicationDirPath() + "/TestHttpMapping.exe";
    IStaticFileResponse response;
    response.setFilePath(path);
    response.enableContentDisposition();
    return response;
}

void StaticFileController::getFile5(IResponse &response)
{
    auto path = IApplication::applicationDirPath() + "/TestHttpMapping.exe";
    IStaticFileResponse fileResponse;
    fileResponse.setFilePath(path);
    response.setContent(&fileResponse);
}
