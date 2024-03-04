#include "IStaticFileResponse.h"
#include "core/base/ICodecUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "web/IWebAssert.h"
#include "web/biscuits/IHttpMime.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

const QString IStaticFileResponse::m_matcherPrefix{"$file:"};

namespace IStaticFileResponseHelper
{
    QString getContentDisposition(const QString& filePath);
    void setFilePath(IResponseWareRaw* raw, const QString& path);
    void checkAndUpdateContentDisposition(bool contentDisposition, IResponseWareRaw* raw);
}

void IStaticFileResponse::enableContentDisposition(bool enabled)
{
    m_enableContentDisposition = enabled;
    IStaticFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

IStaticFileResponse::IStaticFileResponse()
{
}

IStaticFileResponse::IStaticFileResponse(const char *data)
{
    IStaticFileResponseHelper::setFilePath(raw, data);
    IStaticFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

IStaticFileResponse::IStaticFileResponse(const QString &data)
{
    IStaticFileResponseHelper::setFilePath(raw, data);
    IStaticFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

IStaticFileResponse::IStaticFileResponse(IWebCore::IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IStaticFileResponse::setFilePath(const QString &path)
{
    IStaticFileResponseHelper::setFilePath(raw, path);
    IStaticFileResponseHelper::checkAndUpdateContentDisposition(m_enableContentDisposition, raw);
}

void IStaticFileResponse::setContent(const QByteArray &bytes)
{
    Q_UNUSED(bytes);
    qFatal(IConstantUtil::UnVisibleMethod);
}

void IStaticFileResponse::setContent(const QString &content)
{
    Q_UNUSED(content);
    qFatal(IConstantUtil::UnVisibleMethod);
}

void IStaticFileResponse::setContent(const char *content)
{
    Q_UNUSED(content);
    qFatal(IConstantUtil::UnVisibleMethod);
}

void IStaticFileResponse::setInstanceArg(QString &&data)
{
    auto path = data.mid(m_matcherPrefix.length());
    setFilePath(path);
}

bool IStaticFileResponse::canConvertFromString()
{
    return true;
}

bool IStaticFileResponse::matchConvertString(const QString &str)
{
    return str.startsWith(m_matcherPrefix);
}

QSharedPointer<IResponseWare> IStaticFileResponse::createInstance()
{
    return QSharedPointer<IResponseWare>(new IStaticFileResponse);
}

IStaticFileResponse operator"" _file(const char* str, size_t size)
{
    QByteArray array(str, static_cast<int>(size));
    QString name(array);

    IStaticFileResponse response(name);
    return response;
}

QString IStaticFileResponseHelper::getContentDisposition(const QString& filePath)
{
    auto fileName  = QFileInfo(filePath).fileName();
    return QString("attachment;filename=").append(ICodecUtil::urlEncode(fileName));
}

void IStaticFileResponseHelper::setFilePath(IResponseWareRaw* raw, const QString& path)
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

void IStaticFileResponseHelper::checkAndUpdateContentDisposition(bool contentDisposition, IResponseWareRaw* raw)
{
    if(contentDisposition &&raw->content.type == IResponseContent::File
        && !raw->content.contentFilePath.isEmpty()){
        raw->headers["Content-Disposition"]
            = IStaticFileResponseHelper::getContentDisposition(raw->content.contentFilePath);
    }
}

$PackageWebCoreEnd
