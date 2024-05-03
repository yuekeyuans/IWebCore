#include "IMultiPartJar.h"
#include "http/IHttpAssert.h"
#include "http/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

IMultiPartJar::IMultiPartJar() : IJarUnit(nullptr)
{
    qFatal(IConstantUtil::UnVisibleMethod);
}

IResult<IMultiPart> IMultiPartJar::operator[](const QString &name) const
{
    bool ok;
    auto value = getRequestMultiPart (name, ok);
    return {std::move(value), ok};
}

bool IMultiPartJar::containRequestMulitPartName(const QString &name) const
{
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            return true;
        }
    }
    return false;
}

QStringList IMultiPartJar::getRequestMultiPartNames() const
{
    QStringList ret;
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        ret.append (part.name);
    }
    return ret;
}

// 这里的操作是，添加一个invalid multipart;
IMultiPart IMultiPartJar::getRequestMultiPart(const QString &name, bool& ok) const
{
    const auto& jar = m_raw->m_requestMultiParts;
    for(const auto& part : jar){
        if(part.name == name){
            ok = true;
            return part;
        }
    }

    ok = false;
    return IMultiPart::InvalidMulitPart;
}

IResult<IMultiPart> IMultiPartJar::getRequestMultiPart(const QString &name) const
{
    bool ok;
    auto value = getRequestMultiPart(name, ok);
    return {value, ok};
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
        if(!part.fileName.isEmpty ()){
            ret.append (part);
        }
    }
    return ret;
}

$PackageWebCoreEnd
