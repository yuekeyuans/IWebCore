#include "IHttpPathRegexpValidatorInterface.h"
#include "IHttpManage.h"

$PackageWebCoreBegin

void IHttpPathRegexpValidatorInterfaceHelper::registValidator(const QString &name, const QString &validator)
{
    IHttpManage::instance()->registerPathValidator(name, validator);
}

$PackageWebCoreEnd


