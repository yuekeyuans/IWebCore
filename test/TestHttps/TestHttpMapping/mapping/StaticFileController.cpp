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
