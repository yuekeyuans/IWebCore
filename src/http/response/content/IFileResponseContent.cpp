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

const std::string &IFileResponseContent::getType() const
{
    return CLASS_NAME;
}

IStringView IFileResponseContent::getContent()
{
    if(m_dataRaw.m_stringView.length() == 0){
        QFile file(m_path);
        if(file.open(QFile::ReadOnly)){
            m_dataRaw = file.readAll();
            file.close();
        }
    }

    return m_dataRaw.m_stringView;
}

const std::string& IFileResponseContent::getSuggestedMime() const
{
    static const std::string& mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM).m_stringView.toStdString();
    return mime;
}

$PackageWebCoreEnd
