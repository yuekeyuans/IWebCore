#include "IResponseContent.h"

$PackageWebCoreBegin

IResponseContent::~IResponseContent()
{
}

IResponseContent::IResponseContent(IString && data)
    : m_dataRaw(std::move(data))
{
}

IResponseContent::IResponseContent(const IString & data)
    : m_dataRaw(data)
{
}

$PackageWebCoreEnd
