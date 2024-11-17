#include "IMetaType.h"

$PackageWebCoreBegin

IMetaType::IMetaType(QMetaType::Type type, const QString &name)
{
    typeId = type;
    if(name.isEmpty()){
        typeName = QMetaType::typeName(typeId);
    }else{
        typeName = name;
    }
}

bool IMetaType::operator ==(const IMetaType &node) const
{
    if(node.typeId != QMetaType::UnknownType){
        return node.typeId == typeId;
    }
    return node.typeName == typeName;
}

bool IMetaType::operator <(const IMetaType &node) const
{
    return node.typeId > typeId || node.typeName > typeName;
}

$PackageWebCoreEnd
