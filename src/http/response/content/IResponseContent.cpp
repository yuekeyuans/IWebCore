#include "IResponseContent.h"

$PackageWebCoreBegin

IResponseContent::~IResponseContent()
{
}

IResponseContent::IResponseContent(IString && data)
    : m_content(std::move(data))
{
}

IResponseContent::IResponseContent(const IString & data)
    : m_content(data)
{
}

$PackageWebCoreEnd
