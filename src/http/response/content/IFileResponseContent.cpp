#include "IFileResponseContent.h"
#include "http/biscuits/IHttpMime.h"
#include "core/util/IFileUtil.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/response/content/IInvalidReponseContent.h"

$PackageWebCoreBegin

IFileResponseContent::IFileResponseContent(const QString &path)
    : m_path(path)
{
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

$PackageWebCoreEnd
