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

void IResponseContent::setAttribute(IString key, IString value)
{
    if(!m_attribute){
        m_attribute = new QMap<IString, IString>;
    }
    (*m_attribute)[key] = std::move(value);
}

$PackageWebCoreEnd
