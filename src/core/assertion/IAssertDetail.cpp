#include "IAssertDetail.h"

$PackageWebCoreBegin

namespace IAssertDetailHelper{
    QString detailToString(const QMap<IAssertDetail::Type, QString>& infoType
                           , const QMap<QString, QString>& infoStrings);
}

void IAssertDetail::setDetail(IAssertDetail::Type type, const QString &info)
{
    m_detailInfoType[type] = info;
}

QString &IAssertDetail::operator [](IAssertDetail::Type type)
{
    return m_detailInfoType[type];
}

QString &IAssertDetail::operator [](const QString & key)
{
    return m_detailInfoStrings[key];
}

QString IAssertDetail::toString() const
{
    return IAssertDetailHelper::detailToString(m_detailInfoType, m_detailInfoStrings);
}

QString IAssertDetailHelper::detailToString(const QMap<IAssertDetail::Type, QString>& infoType
                                                   , const QMap<QString, QString>& infoStrings)
{
    auto keys = infoType.keys();
    QStringList ret;
    for(auto key : keys){
        QString name = QMetaEnum::fromType<IAssertDetail::Type>().valueToKey(key);
        ret.append(name + ": " + infoType[key]);
    }

    auto stringKeys = infoStrings.keys();
    for(auto key : stringKeys){
        ret.append(key + ": " + infoStrings[key]);
    }

    return ret.join(", ");
}

$PackageWebCoreEnd
