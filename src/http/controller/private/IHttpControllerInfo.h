#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IGadgetInfo.h"
#include "http/base/IUrlActionNode.h"

$PackageWebCoreBegin

struct IHttpControllerInfo : public IGadgetInfo
{
    QVector<IUrlActionNode> m_urlNodes;
};

$PackageWebCoreEnd
