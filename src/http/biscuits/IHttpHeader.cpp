#include "IHttpHeader.h"
#include "core/util/IConstantUtil.h"

$PackageWebCoreBegin

void IHttpHeader::insert(IString key, IString value)
{
    m_header[std::move(key)] = std::move(value);
}

void IHttpHeader::remove(const IString& key)
{
    m_header.erase(key);
}

std::vector<IStringView> IHttpHeader::keys() const
{
    std::vector<IStringView> ret;
    for(const auto& pair : m_header){
        ret.push_back(pair.first.m_view);
    }
    return ret;
}

const IString& IHttpHeader::value(const IString& key) const
{
    for(const auto& pair : m_header){
        if(pair.first == key){
            return pair.second;
        }
    }
    return IConstantUtil::Empty;
}

bool IHttpHeader::contain(const IString& key) const
{
    return m_header.find(key) != m_header.end();
}

bool IHttpHeader::isEmpty() const
{
    return m_header.empty();
}

$PackageWebCoreEnd


