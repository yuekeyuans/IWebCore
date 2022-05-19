#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

class IAssertDetail{
    Q_GADGET
public:
    enum Type{
        File,
        Class,
        Function,
        Line,
        Parameter,
        ReturnType,
        Reason
    };
    Q_ENUM(Type)

    void setDetail(Type type, const QString& info);
    QString& operator [](Type);
    QString& operator [](const QString&);
    QString toString() const;

private:
    QMap<Type, QString> m_detailInfoType;
    QMap<QString, QString> m_detailInfoStrings;
};

$PackageWebCoreEnd
