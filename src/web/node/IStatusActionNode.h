#pragma once

#include "web/biscuits/IHttpStatus.h"
#include "web/node/IMethodNode.h"

$PackageWebCoreBegin

struct IStatusActionNode{
    IHttpStatus httpStatus;
    IMethodNode methodNode;
};

$PackageWebCoreEnd
