#include "IGingerResponse.h"
#include "core/result/IResult.h"
#include "core/base/IFileUtil.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

namespace IGingerResponseHelper
{
    IResult<QString> getRealPath(const QString& path);
}

IGingerResponse::IGingerResponse()
{
    setMime(IHttpMime::TEXT_HTML_UTF8);
}

IGingerResponse::IGingerResponse(const QString& path, QJsonObject obj)
{
    auto realPath = IGingerResponseHelper::getRealPath(path);
    if(!realPath.isOk()){
        QString tip = QString("ginger path is not valid. path:").append(path);
        setInvalid(IHttpStatus::INTERNAL_SERVER_ERROR_500, std::move(tip));
    }
//    IGingerResponseHelper::StringOutput output;
//    ginger::parse(IFileUtil::readFileAsByteArray(realPath).value(), obj, output);
//    this->m_raw->setContent(output.getContent());
//    this->m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
}

//IGingerResponse::IGingerResponse(const QString &path, std::map<std::string, ginger::object> args)
//{
//    auto realPath = IGingerResponseHelper::getRealPath(path);
//    if(!realPath.isOk()){
//        QString tip = QString("ginger path is not valid. path:").append(path);
//        setInvalid(IHttpStatus::INTERNAL_SERVER_ERROR_500, std::move(tip));
//    }
//    IGingerResponseHelper::StringOutput output;
//    ginger::parse(IFileUtil::readFileAsByteArray(realPath).value(), args, output);
//    this->m_raw->setContent(output.getContent());
//    this->m_raw->setMime(IHttpMime::TEXT_HTML_UTF8);
//}

QString IGingerResponse::getPrefixMatcher()
{
    return "$ginger:";
}

IGingerResponse operator"" _ginger(const char* str, size_t size)
{
    Q_UNUSED(size)
    return IGingerResponse(str);
}

// TODO: 这里的参数不太对，应该对应很多路径，但是这里只有一个
IResult<QString> IGingerResponseHelper::getRealPath(const QString &path)
{
    QString realPath = path;
    static $QString prefix{"http.fileService.path"};
    if(!path.startsWith(":/") && !QFileInfo(path).exists() && prefix.isFound()){
        realPath.prepend(prefix);
        if(QFile(realPath).exists()){
            return {realPath, true};
        }
    }

    return {"", false};
}

$PackageWebCoreEnd
