#include "ISortUnit.h"

$PackageWebCoreBegin

QStringList ISortUnit::orders() const
{
    return {};
}

QStringList ISortUnitHelper::sort(const QList<QPair<QString, QStringList> > &)
{
    return {};
}

$PackageWebCoreEnd
