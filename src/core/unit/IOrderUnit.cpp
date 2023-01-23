#include "IOrderUnit.h"

$PackageWebCoreBegin

double IOrderUnit::order() const
{
    return 50.0;
}

QList<IOrderUnit *> IOrderUnit::sortUnit(QList<IOrderUnit *> values)
{
    std::sort(values.begin(), values.end(), [](IOrderUnit* lh, IOrderUnit* rh) -> bool{
        if(lh->order() != rh->order()){
            return lh->order() < rh->order();
        }

        return lh->name() < rh->name();
    });
    return values;
}

$PackageWebCoreEnd

