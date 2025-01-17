﻿#include "IHttpPathValidatorInterface.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

void IHttpPathFunctorValidatorInterfaceHelper::registValidator(const QString &name, std::function<bool (IStringView)> validator)
{
    IHttpManage::instance()->registerPathValidator(name, validator);
}

$PackageWebCoreEnd
