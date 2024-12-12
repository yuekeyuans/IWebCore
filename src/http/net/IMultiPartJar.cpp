#include "IMultiPartJar.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestRaw.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/net/impl/IRequestImpl.h"

$PackageWebCoreBegin

const IMultiPart& IMultiPartJar::operator[](const QString &name) const
{
    auto temp = name.toUtf8();
    return this->operator [](IStringView(temp));
}

const IMultiPart& IMultiPartJar::operator[](const IString& name) const
{
    const auto& jar = m_impl.m_reqRaw.m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return part;
        }
    }
    return IMultiPart::Empty;
}

bool IMultiPartJar::contain(const IString& name) const
{
    const auto& jar = m_impl.m_reqRaw.m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return true;
        }
    }
    return false;
}

bool IMultiPartJar::contain(const QString &name) const
{
    return contain(IString(name.toUtf8()));
}

IStringViewList IMultiPartJar::getKeys() const
{
    IStringViewList ret;
    const auto& jar = m_impl.m_reqRaw.m_requestMultiParts;
    for(const auto& part : jar){
        ret.append (part.name);
    }
    return ret;
}

const IMultiPart& IMultiPartJar::getMultiPart(const IString& name) const
{
    const auto& jar = m_impl.m_reqRaw.m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return part;
        }
    }
    return IMultiPart::Empty;
}

const IMultiPart& IMultiPartJar::getMultiPart(const QString &name) const
{
    return getMultiPart(IString(name.toUtf8()));
}

const QVector<IMultiPart> &IMultiPartJar::getRequestMultiParts() const
{
    return m_impl.m_reqRaw.m_requestMultiParts;
}

QVector<IMultiPart> IMultiPartJar::getRequestFileMultiParts() const
{
    QVector<IMultiPart> ret;
    const auto& jar = m_impl.m_reqRaw.m_requestMultiParts;
    for(const auto& part : jar){
        if(!part.fileName.empty ()){
            ret.append (part);
        }
    }
    return ret;
}

$PackageWebCoreEnd
