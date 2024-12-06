#include "IReturnType.h"

$PackageWebCoreBegin

void *IReturnType::create() const
{
    if(typeId == QMetaType::UnknownType && typeName == "IHttpStatus"){
        return QMetaType::create(QMetaType::Int);
    }
    return QMetaType::create(typeId);
}

void IReturnType::destroy(void *ptr) const
{
    if(typeId == QMetaType::UnknownType && typeName == "IHttpStatus"){
        return QMetaType::destroy(QMetaType::Int, ptr);
    }
    return QMetaType::destroy(typeId, ptr);
}

void IReturnType::resolveValue(IRequestImpl& impl, void *ptr) const
{
    m_resolveFunction(impl, ptr);
}

$PackageWebCoreEnd
