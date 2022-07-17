#include "StaticFileController.h"

StaticFileController::StaticFileController()
{

}

IStaticFileResponse StaticFileController::getFile1()
{
    return QStringLiteral(R"(E:\BaiduNetdiskDownload\壁纸\手机壁纸\2016-02-26 085819.png)");
}
