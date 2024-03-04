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

const QString IFileResponse::m_matcherPrefix{"$file:"};

namespace IFileResponseHelper
{
    static QString getContentDispositionAttachment(const QString& filePath);
    static void setFilePath(IResponseWareRaw* raw, const QString& path);
    static void checkAndUpdateContentDisposition(bool enabled, IResponseWareRaw* raw);
    static $QStringList suffixes{"http.fileService.suffixes"};
}

IFileResponse::IFileResponse()
{
}

IFileResponse::IFileResponse(const char *data)
{
    IFileResponseHelper::setFilePath(raw, data);
    IFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

IFileResponse::IFileResponse(const QString &data)
{
    IFileResponseHelper::setFilePath(raw, data);
    IFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

IFileResponse::IFileResponse(IWebCore::IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IFileResponse::setFilePath(const QString &path)
{
    IFileResponseHelper::setFilePath(raw, path);
    IFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

void IFileResponse::setContent(const QByteArray &bytes)
{
    Q_UNUSED(bytes);
    qFatal(IConstantUtil::UnVisibleMethod);
}

void IFileResponse::setContent(const QString &content)
{
    Q_UNUSED(content);
    qFatal(IConstantUtil::UnVisibleMethod);
}

void IFileResponse::setContent(const char *content)
{
    Q_UNUSED(content);
    qFatal(IConstantUtil::UnVisibleMethod);
}

void IFileResponse::setInstanceArg(QString &&data)
{
    auto path = data.mid(m_matcherPrefix.length());
    setFilePath(path);
}

bool IFileResponse::canConvertFromString()
{
    return true;
}

bool IFileResponse::matchConvertString(const QString &str)
{
    return str.startsWith(m_matcherPrefix);
}

QSharedPointer<IResponseWare> IFileResponse::createInstance()
{
    return QSharedPointer<IResponseWare>(new IFileResponse);
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

void IFileResponseHelper::setFilePath(IResponseWareRaw* raw, const QString& path)
{
    QString realPath = path;
    if(!path.startsWith(":/") && !QFileInfo(path).exists()){
        $QString prefix{"http.fileService.path"};
        if(prefix.isFound()){
            realPath.prepend(prefix);
        }
    }

    if(IConstantUtil::DebugMode){
        if(!QFile(realPath).exists()){
            IAssertInfo info;
            info.reason = QString("filepath: " ).append(realPath);
            $Ast->fatal("static_file_not_exist", info);
        }
    }

    auto suffix = IFileUtil::getFileSuffix(realPath);
    raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    raw->setFileContent(realPath);
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
