#include "IGlobalAst.h"

$PackageWebCoreBegin

IGlobalAst::IGlobalAst()
{
}

void IGlobalAst::loadFromFunction()
{
    addFatal("Assert_Load_Json_Error", "your json format is not correct");
}

$PackageWebCoreEnd
