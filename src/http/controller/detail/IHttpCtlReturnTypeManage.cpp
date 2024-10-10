#include "IHttpCtlReturnTypeManage.h"

$PackageWebCoreBegin

IHttpCtlReturnTypeManage::IHttpCtlReturnTypeManage()
{

}

IHttpControllerActionNode::ReturnType IHttpCtlReturnTypeManage::parseReturnType(const IHttpControllerActionNode &node)
{
    return IHttpControllerActionNode::ReturnType::Void;
}

bool IHttpCtlReturnTypeManage::isReturnTypeValid(const IHttpControllerActionNode &node)
{
    return true;
}

$PackageWebCoreEnd
