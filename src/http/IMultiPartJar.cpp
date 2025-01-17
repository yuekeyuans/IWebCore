﻿#include "IMultiPartJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/detail/IRequestRaw.h"
#include "http/detail/IResponseRaw.h"
#include "http/detail/IRequestImpl.h"

$PackageWebCoreBegin

const IMultiPart& IMultiPartJar::operator[](const QString &name) const
{
    auto temp = name.toUtf8();
    return this->operator [](IStringView(temp));
}

const IMultiPart& IMultiPartJar::operator[](const IString& name) const
{
    const auto& jar = m_impl.m_reqRaw.m_multiParts;
    for(const auto& part : jar){
        if(part.m_name == name){
            return part;
        }
    }
    return IMultiPart::Empty;
}

bool IMultiPartJar::contain(const IString& name) const
{
    const auto& jar = m_impl.m_reqRaw.m_multiParts;
    for(const auto& part : jar){
        if(part.m_name == name){
            return true;
        }
    }
    return false;
}

bool IMultiPartJar::contain(const QString &name) const
{
    return contain(IString(name.toUtf8()));
}

IStringViewList IMultiPartJar::getNames() const
{
    IStringViewList ret;
    const auto& jar = m_impl.m_reqRaw.m_multiParts;
    for(const auto& part : jar){
        ret.append (part.m_name);
    }
    return ret;
}

const IMultiPart& IMultiPartJar::getMultiPart(const IString& name) const
{
    const auto& jar = m_impl.m_reqRaw.m_multiParts;
    for(const IMultiPart& part : jar){
        if(part.m_name == name){
            return part;
        }
    }
    return IMultiPart::Empty;
}

const IMultiPart& IMultiPartJar::getMultiPart(const QString &name) const
{
    return getMultiPart(IString(name.toUtf8()));
}

const std::vector<IMultiPart> &IMultiPartJar::getRequestMultiParts() const
{
    return m_impl.m_reqRaw.m_multiParts;
}

$PackageWebCoreEnd
