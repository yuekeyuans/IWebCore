#include "IReturnType.h"

$PackageWebCoreBegin

void *IReturnType::create() const
{
    if(m_typeId != QMetaType::UnknownType){
        return QMetaType::create(m_typeId);
    }

    if(m_typeName == "IHttpStatus"){
        return new int;
    }else if(m_typeName == "std::string"){
        return new std::string;
    }else if(m_typeName == "IString"){
        return new IString;
    }else if(m_typeName == "IStringView"){
        return new IStringView;
    }else if(m_typeName == "IJson"){
        return new IJson;
    }
    qFatal(m_typeName.c_str());
    return nullptr;
}

void IReturnType::destroy(void *ptr) const
{
    if(m_typeId != QMetaType::UnknownType){
        return QMetaType::destroy(m_typeId, ptr);
    }

    if(m_typeName == "IHttpStatus"){
        return delete static_cast<int*>(ptr);
    }else if(m_typeName == "std::string"){
        return delete static_cast<std::string*>(ptr);
    }else if(m_typeName == "IString"){
        return delete static_cast<IString*>(ptr);
    }else if(m_typeName == "IStringView"){
        return delete static_cast<IStringView*>(ptr);
    }else if(m_typeName == "IJson"){
        return delete static_cast<IJson*>(ptr);
    }
    qFatal("not supported type");
}

$PackageWebCoreEnd
