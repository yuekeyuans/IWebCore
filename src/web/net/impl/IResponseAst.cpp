#include "IResponseAst.h"

$PackageWebCoreBegin

IResponseAst::IResponseAst()
{
}

void IResponseAst::loadFromFunction()
{
    addWarn("iresponse_setHeader_with_empty_value_or_key", "");
}

$PackageWebCoreEnd
