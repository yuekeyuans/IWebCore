#include "IHttpPathFunctorValidatorInterface.h"
#include "IHttpManage.h"

$PackageWebCoreBegin

void IHttpPathFunctorValidatorInterfaceHelper::registValidator(const QString &name, IHttpPathFunctorValidatorWare::Validator validator)
{
    IHttpManage::instance()->registerPathValidator(name, validator);
}

$PackageWebCoreEnd
