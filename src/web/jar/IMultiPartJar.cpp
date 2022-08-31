#include "IMultiPartJar.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IMultiPartJar::IMultiPartJar() : IJarUnit(nullptr)
{
    $Ast->fatal("IMultiPartJar_CREATE_ERROR");
}

bool IMultiPartJar::isValid() const
{
    return m_raw != nullptr;
}

$PackageWebCoreEnd
