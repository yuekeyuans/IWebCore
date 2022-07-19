#include "IStaticFileResponse.h"
#include "base/IFileUtil.h"
#include "web/biscuits/IHttpMime.h"

$PackageWebCoreBegin

const QString IStaticFileResponse::m_matcherPrefix{"$file:"};

IStaticFileResponse::IStaticFileResponse()
{
}

IStaticFileResponse::IStaticFileResponse(const char *data)
{
    auto suffix = IFileUtil::getFileSuffix(data);
    raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    raw->setFileContent(data);
}

IStaticFileResponse::IStaticFileResponse(const QString &data)
{
    auto suffix = IFileUtil::getFileSuffix(data);
    raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    raw->setFileContent(data);
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

$PackageWebCoreEnd
