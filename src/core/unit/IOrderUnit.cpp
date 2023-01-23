#include "IOrderUnit.h"

$PackageWebCoreBegin

QStringList IOrderUnit::orders() const
{
    return {};
}

IOrderUnit::Priority IOrderUnit::priority() const
{
    return Priority::Low;
}

namespace IOrderUnitHelper
{
    QMap<QString, QStringList> toMap(const QList<QPair<QString, QStringList> > &);
    void checkError(const QList<QPair<QString, QStringList> > &);

    // checks
    void checkFirst(const QMap<QString, QStringList>&);
    void checkLast(const QMap<QString, QStringList>&);
}

QStringList IOrderUnitHelper::sort(const QMap<QString, QStringList> &values)
{
    return values.keys();
}

QMap<QString, QStringList> IOrderUnitHelper::toMap(const QList<QPair<QString, QStringList> > & values)
{
    QMap<QString, QStringList> ret;
    for(const auto& pair : values){
        ret[pair.first] = pair.second;
    }
    return ret;
}

void IOrderUnitHelper::checkError(const QList<QPair<QString, QStringList> > &pairs)
{
    using FunType = std::function<void(const QMap<QString, QStringList>&)>;
    static const QVector<FunType> funs = {
        &IOrderUnitHelper::checkFirst,
        &IOrderUnitHelper::checkLast,
    };

    auto map = toMap(pairs);
    for(auto fun : funs){
        fun(map);
    }
}

void IOrderUnitHelper::checkFirst(const QMap<QString, QStringList>& map)
{

}

void IOrderUnitHelper::checkLast(const QMap<QString, QStringList>& map)
{
    Q_UNUSED(map)
}

$PackageWebCoreEnd
