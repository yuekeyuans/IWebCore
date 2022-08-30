#include "ISessionJar.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

ISessionJar::ISessionJar() : IJarUnit(nullptr)
{
    $Ast->fatal("ISessionJar_CREATE_ERROR");
}

bool ISessionJar::isValid() const
{
    return raw !=nullptr;
}

$PackageWebCoreEnd
