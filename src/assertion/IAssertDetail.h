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
        ReturnValue,
        };
    Q_ENUM(Type)

    void setDetail(Type type, const QString& info);
    QString& operator [](Type);
    QString toString() const;

private:
    QMap<Type, QString> m_detailInfo;
};

$PackageWebCoreEnd
