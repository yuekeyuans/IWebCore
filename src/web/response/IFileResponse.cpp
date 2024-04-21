#include "IFileResponse.h"
#include "core/base/ICodecUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "web/IWebAssert.h"
#include "web/biscuits/IHttpMime.h"
#include "web/controller/IHttpManage.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IFileResponseHelper
{
    static QString getContentDispositionAttachment(const QString& filePath);
    static bool setFilePath(IResponseWareRaw* raw, const QString& path);
    static void checkAndUpdateContentDisposition(IResponseWareRaw* raw);
}

IFileResponse::IFileResponse()
{
}

IFileResponse::IFileResponse(const char *data)
{
    if(IFileResponseHelper::setFilePath(m_raw, data)){
        IFileResponseHelper::checkAndUpdateContentDisposition(m_raw);
    }else{
        setInvalid(IHttpStatus::NOT_FOUND_404, "file not found");
    }
}

IFileResponse::IFileResponse(const QString &data)
{
    if(IFileResponseHelper::setFilePath(m_raw, data)){
        IFileResponseHelper::checkAndUpdateContentDisposition(m_raw);
    }else{
        setInvalid(IHttpStatus::NOT_FOUND_404, "file not found");
    }
}

void IFileResponse::enableContentDisposition()
{
    m_raw->headers["Content-Disposition"] = IFileResponseHelper::getContentDispositionAttachment(m_raw->content.contentFilePath);
}

QString IFileResponse::getPrefixMatcher()
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

QString IFileResponseHelper::getContentDispositionAttachment(const QString& filePath)
{
    auto fileName  = QFileInfo(filePath).fileName();
    return QString("attachment;filename=").append(ICodecUtil::urlEncode(fileName));
}

// TODO: 这里的参数不太对，应该对应很多路径，但是这里只有一个
bool IFileResponseHelper::setFilePath(IResponseWareRaw* raw, const QString& path)
{
    QString realPath = path;
    if(!path.startsWith(":/") && !QFileInfo(path).exists()){
        $QString prefix{"http.fileService.path"};
        if(prefix.isFound()){
            realPath.prepend(prefix);
        }
    }

    if(QFile(realPath).exists()){
        auto suffix = IFileUtil::getFileSuffix(realPath);
        raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
        raw->setFileContent(realPath);
        return true;
    }
    return false;
}

void IFileResponseHelper::checkAndUpdateContentDisposition(IResponseWareRaw* raw)
{
    static $Bool enabled {"http.fileService.contentDisposition.enabled"};
    static $QStringList suffixes{"http.fileService.contentDisposition.suffixes"};
    if(enabled
            && raw->content.type == IResponseContent::File
            && !raw->content.contentFilePath.isEmpty()
            && suffixes.isFound()
            && suffixes.value().contains(IFileUtil::getFileSuffix(raw->content.contentFilePath)))
    {
        raw->headers["Content-Disposition"] = IFileResponseHelper::getContentDispositionAttachment(raw->content.contentFilePath);
    }
}

$PackageWebCoreEnd
