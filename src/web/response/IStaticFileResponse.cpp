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

void IStaticFileResponse::setInstanceArg(QString &&data)
{
    auto suffix = IFileUtil::getFileSuffix(data);
    raw->setMime(IHttpMimeHelper::getSuffixMime(suffix));
    raw->setFileContent(data.mid(m_matcherPrefix.length()));
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
