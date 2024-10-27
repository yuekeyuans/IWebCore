#include "IHttpCtlReturnTypeManage.h"

$PackageWebCoreBegin

IHttpCtlReturnTypeManage::IHttpCtlReturnTypeManage()
{

}

IHttpRouteLeaf::ReturnType IHttpCtlReturnTypeManage::parseReturnType(const IHttpRouteLeaf &node)
{
    return IHttpRouteLeaf::ReturnType::Void;
}

bool IHttpCtlReturnTypeManage::isReturnTypeValid(const IHttpRouteLeaf &node)
{
    return true;
}

$PackageWebCoreEnd
