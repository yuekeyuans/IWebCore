#include "IHttpPathRegexpValidatorInterface.h"
#include "IHttpManage.h"

$PackageWebCoreBegin

void IHttpPathRegexpValidatorInterfaceHelper::registValidator(const QString &name, IHttpPathRegexpValidatorWare::Validator validator)
{
    IHttpManage::instance()->registerPathValidator(name, validator);
}

$PackageWebCoreEnd


