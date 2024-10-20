#include "IHttpCtlReturnTypeManage.h"

$PackageWebCoreBegin

IHttpCtlReturnTypeManage::IHttpCtlReturnTypeManage()
{

}

IHttpRouteLeafNode::ReturnType IHttpCtlReturnTypeManage::parseReturnType(const IHttpRouteLeafNode &node)
{
    return IHttpRouteLeafNode::ReturnType::Void;
}

bool IHttpCtlReturnTypeManage::isReturnTypeValid(const IHttpRouteLeafNode &node)
{
    return true;
}

$PackageWebCoreEnd
