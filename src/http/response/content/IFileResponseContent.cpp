#include "IFileResponseContent.h"
#include "core/util/IConstantUtil.h"
#include "core/util/IFileUtil.h"
#include "http/biscuits/IHttpMime.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/response/content/IInvalidReponseContent.h"

$PackageWebCoreBegin

IFileResponseContent::IFileResponseContent(IString && value)
    : IResponseContent(std::move(value))
{
    setAttribute(&IConstantUtil::Type, &IFileResponseContent::Type);
    m_function = [](IResponseRaw&){
        qFatal("here should be function to resolve file");
    };
}

IFileResponseContent::IFileResponseContent(const IString & value)
    : IResponseContent(value)
{
    setAttribute(&IConstantUtil::Type, &IFileResponseContent::Type);
    m_function = [](IResponseRaw&){
        qFatal("here should be function to resolve file, see IFileResponse");
    };
}

$PackageWebCoreEnd
