#include "IStaticFileResponse.h"
#include "base/IFileUtil.h"
#include "base/ICodecUtil.h"
#include "web/biscuits/IHttpMime.h"

$PackageWebCoreBegin

const QString IStaticFileResponse::m_matcherPrefix{"$file:"};

namespace IStaticFileResponseHelper
{
    QString getContentDisposition(const QString& filePath);
}

void IStaticFileResponse::enableContentDisposition(bool enabled)
{
    m_enableContentDisposition = true;

    if(raw->content.type == IResponseContent::File && !raw->content.contentFilePath.isEmpty()){
        raw->headers["Content-Disposition"]
            = IStaticFileResponseHelper::getContentDisposition(raw->content.contentFilePath);
    }
}

IStaticFileResponse::IStaticFileResponse()
{
}

IStaticFileResponse::IStaticFileResponse(const char *data)
{
    auto suffix = IFileUtil::getFileSuffix(data);
    raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    raw->setFileContent(data);

    if(m_enableContentDisposition &&raw->content.type == IResponseContent::File
        && !raw->content.contentFilePath.isEmpty()){
        raw->headers["Content-Disposition"]
            = IStaticFileResponseHelper::getContentDisposition(raw->content.contentFilePath);
    }
}

IStaticFileResponse::IStaticFileResponse(const QString &data)
{
    auto suffix = IFileUtil::getFileSuffix(data);
    raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    raw->setFileContent(data);

    if(m_enableContentDisposition && raw->content.type == IResponseContent::File
        && !raw->content.contentFilePath.isEmpty()){
        raw->headers["Content-Disposition"]
            = IStaticFileResponseHelper::getContentDisposition(raw->content.contentFilePath);
    }
}

IStaticFileResponse::IStaticFileResponse(IWebCore::IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IStaticFileResponse::setFilePath(const QString &path)
{
    // TODO: 理论上这个没有问题， 因为 用户一般不会调用 setInstanceArg 这个函数
    if(raw->mimeString.isEmpty() || raw->mimeString == "UNKNOWN"){
        auto suffix = IFileUtil::getFileSuffix(path);
        raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    }
    raw->setFileContent(path);

    if(m_enableContentDisposition && raw->content.type == IResponseContent::File
        && !raw->content.contentFilePath.isEmpty()){
        raw->headers["Content-Disposition"]
            = IStaticFileResponseHelper::getContentDisposition(raw->content.contentFilePath);
    }
}

void IStaticFileResponse::setContent(const QByteArray &bytes)
{
    Q_UNUSED(bytes);
    // 覆盖文件
}

void IStaticFileResponse::setContent(const QString &content)
{
    Q_UNUSED(content);
    // 覆盖文件
}

void IStaticFileResponse::setContent(const char *content)
{
    Q_UNUSED(content);
    // 覆盖文件
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

$PackageWebCoreEnd
