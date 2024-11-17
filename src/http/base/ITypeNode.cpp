#include "ITypeNode.h"

$PackageWebCoreBegin

ITypeNode::ITypeNode(QMetaType::Type type, const QString &name)
{
    typeId = type;
    if(name.isEmpty()){
        typeName = QMetaType::typeName(typeId);
    }else{
        typeName = name;
    }
}

bool ITypeNode::operator ==(const ITypeNode &node) const
{
    if(node.typeId != QMetaType::UnknownType){
        return node.typeId == typeId;
    }
    return node.typeName == typeName;
}

bool ITypeNode::operator <(const ITypeNode &node) const
{
    return node.typeId > typeId || node.typeName > typeName;
}

$PackageWebCoreEnd
