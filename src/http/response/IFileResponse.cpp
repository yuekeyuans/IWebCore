#include "IFileResponse.h"
#include "core/util/ICodecUtil.h"
#include "core/util/IConstantUtil.h"
#include "core/util/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "http/biscuits/IHttpMime.h"
#include "http/invalid/IHttpNotFoundInvalid.h"

$PackageWebCoreBegin

namespace detail
{
    static QString getContentDispositionAttachment(const QString& filePath);
    static bool setFilePath(IResponseRaw* raw, const QString& path);
    static void checkAndUpdateContentDisposition(IResponseRaw* raw);
}

IFileResponse::IFileResponse()
{
}

IFileResponse::IFileResponse(const QString &data)
{
    if(detail::setFilePath(m_raw, data)){
        detail::checkAndUpdateContentDisposition(m_raw);
    }else{
        m_raw->setContent(IHttpNotFoundInvalid("file not found"));
    }
}

IFileResponse::IFileResponse(const std::string &data)
    : IFileResponse(QString::fromStdString(data))
{
}

// TODO: fix here
void IFileResponse::enableContentDisposition()
{
//    m_raw->headers.insert("Content-Disposition",
//                                     detail::getContentDispositionAttachment(m_raw->content.contentString));
}

std::string IFileResponse::prefixMatcher()
{
    return "$file:";
}

IFileResponse operator"" _file(const char* str, size_t size)
{
    QByteArray array(str, static_cast<int>(size));
    QString name(array);

    IFileResponse response(name);
    return response;
}

QString detail::getContentDispositionAttachment(const QString& filePath)
{
    auto fileName  = QFileInfo(filePath).fileName();
    return QString("attachment;filename=").append(ICodecUtil::urlEncode(fileName));
}

// TODO: fixme
// TODO: 这里的参数不太对，应该对应很多路径，但是这里只有一个
bool detail::setFilePath(IResponseRaw* raw, const QString& path)
{
//    QString realPath = path;
//    if(!path.startsWith(":/") && !QFileInfo(path).exists()){
//        $QString prefix{"/http/fileService/path"};
//        realPath.prepend(*prefix);

//    }

//    if(QFile(realPath).exists()){
//        auto suffix = IFileUtil::getFileSuffix(realPath);
//        raw->setMime(IHttpMimeUtil::getSuffixMime(suffix));
//        raw->setFileContent(realPath);
//        return true;
//    }
    return false;
}

void detail::checkAndUpdateContentDisposition(IResponseRaw* raw)
{
//    static $Bool enabled {"/http/fileService/contentDisposition/enabled"};
//    static $QStringList suffixes{"/http/fileService/contentDisposition/suffixes"};
//    if(*enabled
//            && raw->content.type == IResponseContent::Type::File
//            && !raw->content.contentString.isEmpty()
//            && suffixes.value().contains(IFileUtil::getFileSuffix(raw->content.contentString)))
//    {
//        raw->headers.insert("Content-Disposition",
//                                       detail::getContentDispositionAttachment(raw->content.contentString));
//    }
}

$PackageWebCoreEnd
