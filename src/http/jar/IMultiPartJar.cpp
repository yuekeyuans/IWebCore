#include "IMultiPartJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/IHttpAssert.h"
#include "http/net/impl/IRequestRaw.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

IMultiPartJar::IMultiPartJar() : IJarUnit(nullptr)
{
    IGlobalAbort::abortUnVisibleMethod();
}

IMultiPart IMultiPartJar::operator[](const QString &name) const
{
    auto temp = name.toUtf8();
    return this->operator [](IStringView(temp));
}

IMultiPart IMultiPartJar::operator[](IStringView name) const
{
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return part;
        }
    }
    return {};
}

bool IMultiPartJar::containRequestMulitPartName(IStringView name) const
{
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return true;
        }
    }
    return false;
}

bool IMultiPartJar::containRequestMulitPartName(const QString &name) const
{
    auto temp = name.toUtf8();
    return containRequestMulitPartName(IStringView(temp));
}

IStringViewList IMultiPartJar::getRequestMultiPartNames() const
{
    IStringViewList ret;
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        ret.append (part.name);
    }
    return ret;
}

IMultiPart IMultiPartJar::getRequestMultiPart(IStringView name) const
{
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return part;
        }
    }
    return {};
}

IMultiPart IMultiPartJar::getRequestMultiPart(const QString &name) const
{
    auto temp = name.toUtf8();
    return getRequestMultiPart(IStringView(temp));
}

const QVector<IMultiPart> &IMultiPartJar::getRequestMultiParts() const
{
    return m_raw->m_requestMultiParts;
}

QVector<IMultiPart> IMultiPartJar::getRequestFileMultiParts() const
{
    QVector<IMultiPart> ret;
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        if(!part.fileName.empty ()){
            ret.append (part);
        }
    }
    return ret;
}

$PackageWebCoreEnd
