#include "IStaticFileResponse.h"
#include "base/IFileUtil.h"

$PackageWebCoreBegin

const QString IStaticFileResponse::m_matcherPrefix{"$file:"};

IStaticFileResponse::IStaticFileResponse()
{
}

IStaticFileResponse::IStaticFileResponse(const char *data)
{
    m_fileName = QString(data);
}

IStaticFileResponse::IStaticFileResponse(const QString &data)
{
    m_fileName = data;
}

IStaticFileResponse::IStaticFileResponse(IWebCore::IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IStaticFileResponse::setInstanceArg(QString &&data)
{
    m_fileName = data.mid(m_matcherPrefix.length()).toUtf8();
}

bool IStaticFileResponse::canConvertFromString()
{
    return true;
}

bool IStaticFileResponse::matchConvertString(const QString &str)
{
    return str.startsWith(m_matcherPrefix);
}

void IStaticFileResponse::updateDelayedResponse()
{
    if(!IFileUtil::isFileExist(m_fileName)){
        // TODO: 这个应该是什么状态？ 是 redirect 还是报错
    }

    QFileInfo fileInfo(m_fileName);
    raw->setMime(IHttpMimeHelper::getSuffixMime(fileInfo.suffix()));
    this->setContent(IFileUtil::readFileAsByteArray(m_fileName));
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
