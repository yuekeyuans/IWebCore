#include "IAssertDetail.h"

$PackageWebCoreBegin

namespace IAssertDetailHelper{
    QString detailToString(const QMap<IAssertDetail::Type, QString>& info);
}

void IAssertDetail::setDetail(IAssertDetail::Type type, const QString &info)
{
    m_detailInfo[type] = info;
}

QString &IAssertDetail::operator [](IAssertDetail::Type type)
{
    return m_detailInfo[type];
}

QString IAssertDetail::toString() const
{
    return IAssertDetailHelper::detailToString(m_detailInfo);
}

inline QString IAssertDetailHelper::detailToString(const QMap<IAssertDetail::Type, QString>& info)
{
    auto keys = info.keys();
    QStringList ret;
    for(auto key : keys){
        QString name = QMetaEnum::fromType<IAssertDetail::Type>().valueToKey(key);
        ret.append(name + ": " + info[key]);
    }
    return ret.join(", ");
}

$PackageWebCoreEnd
