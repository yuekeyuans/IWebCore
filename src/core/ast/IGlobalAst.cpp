#include "IGlobalAst.h"

$PackageWebCoreBegin

void IGlobalAst::fatal(IGlobalAst::Type type)
{
    QString name = QMetaEnum::fromType<IGlobalAst::Type>().valueToKey(type);
    this->IAstInterface::fatal(name);
}

void IGlobalAst::fatal(const QString &name)
{
    this->IAstInterface::fatal(name);
}

void IGlobalAst::fatal(const QString &name, const IAstInfo &info)
{
    this->IAstInterface::fatal(name, info);
}

void IGlobalAst::loadFromFunction()
{
    addFatal("Assert_Load_Json_Error", "your json format is not correct");
    addFatal("UnImplimentedMethod", "this method is not implimented.");
    addFatal("EnableBluePrintParamError", "");
}

$PackageWebCoreEnd
