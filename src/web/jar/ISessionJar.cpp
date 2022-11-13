#include "ISessionJar.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

ISessionJar::ISessionJar() : IJarUnit(nullptr)
{
    $Ast->fatal("ISessionJar_CREATE_ERROR");
}

$PackageWebCoreEnd
