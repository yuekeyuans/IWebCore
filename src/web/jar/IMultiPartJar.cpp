#include "IMultiPartJar.h"

$PackageWebCoreBegin

IMultiPartJar::IMultiPartJar()
{

}

bool IMultiPartJar::isValid() const
{
    return raw != nullptr;
}

$PackageWebCoreEnd
