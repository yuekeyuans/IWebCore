#include "IControllerPathValidatorInterface.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

void IControllerPathValidatorInterfaceProxy::registerValidator(const QString &name, const QString &regexp)
{
    IControllerManage::instance()->registerPathValidator(name, regexp);
}

void IControllerPathValidatorInterfaceProxy::registerValidator(const QString &name, ValidateFun function)
{
    IControllerManage::instance()->registerPathValidator(name, function);
}

$PackageWebCoreEnd
