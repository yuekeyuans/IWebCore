#include "IFileResponse.h"
#include "core/base/ICodecUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "web/IWebAssert.h"
#include "web/biscuits/IHttpMime.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

namespace IFileResponseHelper
{
    static QString getContentDispositionAttachment(const QString& filePath);
    static bool setFilePath(IResponseWareRaw* raw, const QString& path);
    static void checkAndUpdateContentDisposition(bool enabled, IResponseWareRaw* raw);
    static $QStringList suffixes{"http.fileService.suffixes"};
}

// TODO: 检查 这里判断 setInvalid 方法不能使用的问题。
IFileResponse::IFileResponse(const char *data)
{
    if(IFileResponseHelper::setFilePath(m_raw, data)){
        IFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, m_raw);
    }else{
        setInvalid(IHttpStatus::NOT_FOUND_404, "file not found");
    }
}

IFileResponse::IFileResponse(const QString &data)
{
    if(IFileResponseHelper::setFilePath(m_raw, data)){
        IFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, m_raw);
    }else{
        setInvalid(IHttpStatus::NOT_FOUND_404, "file not found");
    }
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

void IFileResponseHelper::checkAndUpdateContentDisposition(bool enabled, IResponseWareRaw* raw)
{
    if(enabled
            && raw->content.type == IResponseContent::File
            && !raw->content.contentFilePath.isEmpty()
            && IFileResponseHelper::suffixes.isFound()
            && IFileResponseHelper::suffixes.value().contains(IFileUtil::getFileSuffix(raw->content.contentFilePath))){
        raw->headers["Content-Disposition"]
                = IFileResponseHelper::getContentDispositionAttachment(raw->content.contentFilePath);
    }
}

$PackageWebCoreEnd
