#include "IStaticFileResponse.h"
#include "base/IFileUtil.h"

$PackageWebCoreBegin

const QString IStaticFileResponse::m_matcherPrefix{"$file:"};

IStaticFileResponse::IStaticFileResponse()
{
}

IStaticFileResponse::IStaticFileResponse(const char *data)
{
    raw->setFileContent(data);
}

IStaticFileResponse::IStaticFileResponse(const QString &data)
{
    raw->setFileContent(data);
}

IStaticFileResponse::IStaticFileResponse(IWebCore::IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IStaticFileResponse::setInstanceArg(QString &&data)
{
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

void IStaticFileResponse::updateDelayedResponse()
{
//    if(!IFileUtil::isFileExist(m_fileName)){
//        // TODO: 这个应该是什么状态？ 是 redirect 还是报错
//    }

//    QFileInfo fileInfo(m_fileName);
//    raw->setMime(IHttpMimeHelper::getSuffixMime(fileInfo.suffix()));
//    this->setContent(IFileUtil::readFileAsByteArray(m_fileName));
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
