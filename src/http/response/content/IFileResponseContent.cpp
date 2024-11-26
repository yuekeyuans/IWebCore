#include "IFileResponseContent.h"
#include "http/biscuits/IHttpMime.h"
#include "core/util/IFileUtil.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/response/content/IInvalidReponseContent.h"

$PackageWebCoreBegin

IFileResponseContent::IFileResponseContent(const QString &path)
    : m_path(path)
{
    if(!QFileInfo(m_path).exists()){
        m_excess = new IInvalidReponseContent(IHttpNotFoundInvalid("file not found"));
    }
}

int IFileResponseContent::getSize()
{
    return QFileInfo(m_path).size();
}

IStringView IFileResponseContent::getType()
{
    static const std::string type = "IFileResponseContent";
    return type;
}

IStringView IFileResponseContent::getContent()
{
    if(m_dataRaw.toStringView().length() == 0){
        QFile file(m_path);
        if(file.open(QFile::ReadOnly)){
            m_dataRaw = file.readAll();
            file.close();
        }
    }

    return m_dataRaw.toStringView();
}

IStringView IFileResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM).toStdString();
    return mime;
}

$PackageWebCoreEnd
