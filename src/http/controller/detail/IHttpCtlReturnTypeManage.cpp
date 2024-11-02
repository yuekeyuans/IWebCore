#include "IHttpCtlReturnTypeManage.h"

$PackageWebCoreBegin

IHttpCtlReturnTypeManage::IHttpCtlReturnTypeManage()
{

}

IHttpAction::ReturnType IHttpCtlReturnTypeManage::parseReturnType(const IHttpAction &node)
{
    return IHttpAction::ReturnType::Void;
}

bool IHttpCtlReturnTypeManage::isReturnTypeValid(const IHttpAction &node)
{
    return true;
}

$PackageWebCoreEnd
