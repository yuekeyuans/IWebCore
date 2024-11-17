#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITypeNode
{
public:
    ITypeNode() = default;
    ITypeNode(QMetaType::Type, const QString& = {});
    bool operator ==(const ITypeNode&) const;
    bool operator <(const ITypeNode&) const;

public:
    QMetaType::Type typeId{QMetaType::UnknownType};
    QString typeName;
};

$PackageWebCoreEnd
