#include "IHttpCtlReturnTypeManage.h"

$PackageWebCoreBegin

IHttpCtlReturnTypeManage::IHttpCtlReturnTypeManage()
{

}

IHttpControllerAction::ReturnType IHttpCtlReturnTypeManage::parseReturnType(const IHttpControllerAction &node)
{
    return IHttpControllerAction::ReturnType::Void;
}

bool IHttpCtlReturnTypeManage::isReturnTypeValid(const IHttpControllerAction &node)
{
    return true;
}

$PackageWebCoreEnd
