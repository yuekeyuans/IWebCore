#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "http/IHttpTaskCatagory.h"

$PackageWebCoreBegin

class IRequest;
class IHttpResolverFilterWare
{
public:
    enum class Type{
        FirstLine,
        Header,
        Body,
        EndState,
        Invalid,
        GenerateData
    };
public:
    void filter(IRequest&) = 0;
    Type getType() const;

protected:
    Type m_type;
};

inline IHttpResolverFilterWare::Type IHttpResolverFilterWare::getType() const
{
    return m_type;
}

template<typename T, bool enabled>
class IHttpResolverFilterInterface : public IHttpResolverFilterWare,
        public ITaskWareUnit<T, IHttpTaskCatagory, enabled>, public ISingletonUnit<T>
{
};

$PackageWebCoreEnd
