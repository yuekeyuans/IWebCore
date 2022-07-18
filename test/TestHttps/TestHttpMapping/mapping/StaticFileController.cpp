#include "StaticFileController.h"

StaticFileController::StaticFileController()
{

}

IStaticFileResponse StaticFileController::getFile1()
{
    auto path = IApplication::applicationDirPath();
    return path + "/TestHttpMapping.exe";
    //    return QStringLiteral(R"(E:\BaiduNetdiskDownload\壁纸\手机壁纸\2016-02-26 085819.png)");
}

IStaticFileResponse StaticFileController::getFile2()
{
    QString path = __FILE__;
    auto file = QFileInfo(path).absolutePath() + "/demoImage.png";
    qDebug() << file;
    return file;
}
