#include "IControllerPathValidatorInterface.h"

#include "controller/IControllerManage.h"

$PackageWebCoreBegin

void IControllerPathValidatorInterfaceProxy::registerValidator(const QString &name, const QString &regexp)
{
    IControllerManage::registerPathValidator(name, regexp);
}

void IControllerPathValidatorInterfaceProxy::registerValidator(const QString &name, ValidateFun function)
{
    IControllerManage::registerPathValidator(name, function);
}

$PackageWebCoreEnd
