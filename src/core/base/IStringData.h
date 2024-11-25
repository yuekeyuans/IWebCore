#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IStringData
{
private:
    enum class Type{
        Invalid =0,
        QByteArray,
        StdString,
        IStringView
    };
    union {
        QByteArray m_qByteArray;
        std::string m_stdString;
        IStringView m_iStringView;
    };

public:
    IStringData();
    ~IStringData();
    IStringData(const QString&);
    IStringData(QByteArray&&);
    IStringData(const QByteArray&);
    IStringData(std::string&&);
    IStringData(const std::string&);
    IStringData(IStringView);

public:
    IStringView toStringView() &;
    IStringView toStringView() && = delete;

private:
    Type m_type{Type::Invalid};
};

$PackageWebCoreEnd
