#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

// TODO: 重构使用方式

struct IUrlNode
{
public:
    static IUrlNode create(const QString& url);

public:
    QString url;
    QList<IUrlFragmentNode> nodes;
};

$PackageWebCoreEnd
