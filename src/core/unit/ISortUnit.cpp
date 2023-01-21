#include "ISortUnit.h"

$PackageWebCoreBegin

QStringList ISortUnit::orders() const
{
    return {};
}


namespace ISortUnitHelper
{

}

QStringList ISortUnitHelper::sort(const QList<QPair<QString, QStringList> > &)
{
    return {};
}

$PackageWebCoreEnd
