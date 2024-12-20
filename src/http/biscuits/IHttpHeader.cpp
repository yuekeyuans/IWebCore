﻿#include "IHttpHeader.h"
#include "core/util/IConstantUtil.h"

$PackageWebCoreBegin

void IHttpHeader::insert(IString key, IString value)
{
    m_header[std::move(key)].push_back(std::move(value));
}

void IHttpHeader::insert(IString key, const std::vector<IString> &value)
{
    m_header.emplace(std::move(key), value);
}

void IHttpHeader::replace(IString key, IString value)
{
    m_header.erase(key);
    m_header[std::move(key)].push_back(std::move(value));
}

void IHttpHeader::remove(const IString& key, const IString& value)
{
    if(m_header.find(key) != m_header.end()){
        auto& vec = m_header.at(key);
        vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
    }
}

void IHttpHeader::clear(const IString& key)
{
    m_header.erase(key);
}

std::vector<IStringView> IHttpHeader::keys() const
{
    std::vector<IStringView> ret;
    for(const auto& pair : m_header){
        ret.push_back(pair.first.m_stringView);
    }
    return ret;
}

const std::vector<IString> &IHttpHeader::values(const IString& key) const
{
    if(m_header.find(key) != m_header.end()){
        return m_header.at(key);
    }
    return IConstantUtil::EmptyVector;
}

const IString &IHttpHeader::value(const IString &key) const
{
    const auto& vals = values(key);
    if(vals.empty()){
        return IConstantUtil::Empty;
    }
    return vals.front();
}

bool IHttpHeader::contain(const IString &key) const
{
    return m_header.find(key) != m_header.end();
}

bool IHttpHeader::isEmpty() const
{
    return m_header.empty();
}

$PackageWebCoreEnd


