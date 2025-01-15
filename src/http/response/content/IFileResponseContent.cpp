#include "IFileResponseContent.h"
#include "core/util/IConstantUtil.h"
#include "core/util/IFileUtil.h"
#include "core/util/ICodecUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/detail/IResponseRaw.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/response/content/IInvalidReponseContent.h"

$PackageWebCoreBegin

namespace detail
{
    static void fileResponseProcessor(const IResponseContent& content, IResponseRaw& raw);
    static IString createDispoisition(const IString&);
    IStringView findMime(const IString&);
}

IFileResponseContent::IFileResponseContent(IString && value)
    : IResponseContent(std::move(value))
{
    setAttribute(&IConstantUtil::Type, &IFileResponseContent::Type);
    m_function = detail::fileResponseProcessor;
}

IFileResponseContent::IFileResponseContent(const IString & value)
    : IResponseContent(value)
{
    setAttribute(&IConstantUtil::Type, &IFileResponseContent::Type);
    m_function = detail::fileResponseProcessor;
}

void detail::fileResponseProcessor(const IResponseContent &content, IResponseRaw &raw)
{
    QFileInfo info(content.m_content.m_view.toQString());
    if(!info.exists()){
        raw.setContent(IHttpNotFoundInvalid());
        return;
    }

    auto data = IFileUtil::readFileAsByteArray(info.absoluteFilePath());
    raw.setContent(new IResponseContent(std::move(data)));
    if(true && content.m_attribute
            && content.m_attribute->contains(IFileResponseContent::ContentDispoistion)
            && content.m_attribute->operator [](IFileResponseContent::ContentDispoistion) == IConstantUtil::True)
    {
        raw.m_headers.insert(IHttpHeader::ContentDisposition, detail::createDispoisition(content.m_content));
    }

    if(false || !content.m_attribute
             || !content.m_attribute->contains(IFileResponseContent::ContentTypeEnabled)
             || content.m_attribute->operator [](IFileResponseContent::ContentTypeEnabled) != IConstantUtil::False)
    {
        auto mime = detail::findMime(content.m_content);
        if(mime != IHttpMimeUtil::MIME_UNKNOWN_STRING.m_view){
            raw.m_headers.insert(IHttpHeader::ContentType, mime);
        }
    }
}

IString detail::createDispoisition(const IString & data)
{
    auto path =data.m_view.toQString();
    auto fileName  = QFileInfo(path).fileName();
    return (QString("attachment;filename=").append(ICodecUtil::urlEncode(fileName))).toUtf8();
}

IStringView detail::findMime(const IString& data)
{
    auto suffix = QFileInfo(data.m_view.toQString()).suffix();
    return IHttpMimeUtil::getSuffixMime(IString(suffix.toUtf8()));
}

$PackageWebCoreEnd
