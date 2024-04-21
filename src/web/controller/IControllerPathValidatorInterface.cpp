#include "IHttpPathRegexpValidatorInterface.h"
#include "web/controller/IHttpManage.h"

$PackageWebCoreBegin

void IControllerPathValidatorInterfaceHelper::registerValidator(const QString &name, const QString &regexp)
{
    IHttpManage::instance()->registerPathValidator(name, regexp);
}

void IControllerPathValidatorInterfaceHelper::registerValidator(const QString &name, ValidateFun function)
{
    IHttpManage::instance()->registerPathValidator(name, function);
}

$PackageWebCoreEnd
