#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/base/IGadgetInfo.h"
#include "http/controller/private/IHttpControllerActionNode.h"

$PackageWebCoreBegin

struct IHttpControllerInfo : public IGadgetInfo
{
    QVector<IHttpControllerActionNode> m_urlNodes;
};

$PackageWebCoreEnd
