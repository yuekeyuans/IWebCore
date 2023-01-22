#include "IOrderUnit.h"

$PackageWebCoreBegin

QStringList IOrderUnit::orders() const
{
    return {};
}


namespace IOrderUnitHelper
{

}

QStringList IOrderUnitHelper::sort(const QList<QPair<QString, QStringList> > &)
{
    return {};
}

$PackageWebCoreEnd
