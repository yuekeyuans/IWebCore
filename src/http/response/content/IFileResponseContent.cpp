#include "IFileResponseContent.h"
#include "http/biscuits/IHttpMime.h"
#include "core/util/IFileUtil.h"
#include "http/invalid/IHttpNotFoundInvalid.h"
#include "http/response/content/IInvalidReponseContent.h"

$PackageWebCoreBegin

IFileResponseContent::IFileResponseContent(IString && value)
    : IResponseContent(std::move(value))
{
    m_function = [](IResponseRaw&){
        qFatal("here should be function to resolve file");
    };
}

IFileResponseContent::IFileResponseContent(const IString & value)
    : IResponseContent(value)
{
    m_function = [](IResponseRaw&){
        qFatal("here should be function to resolve file, see IFileResponse");
    };
}

$PackageWebCoreEnd
