#include "IReturnType.h"

$PackageWebCoreBegin

void *IReturnType::create() const
{
    if(m_typeId == QMetaType::UnknownType && m_typeName == "IHttpStatus"){
        return QMetaType::create(QMetaType::Int);
    }
    return QMetaType::create(m_typeId);
}

void IReturnType::destroy(void *ptr) const
{
    if(m_typeId == QMetaType::UnknownType && m_typeName == "IHttpStatus"){
        return QMetaType::destroy(QMetaType::Int, ptr);
    }
    return QMetaType::destroy(m_typeId, ptr);
}

void IReturnType::resolveValue(IRequestImpl& impl, void *ptr) const
{
    m_resolveFunction(impl, ptr);
}

$PackageWebCoreEnd
