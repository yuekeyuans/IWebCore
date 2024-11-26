#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IStringData {
private:
    enum class Type {
        Invalid = 0,
        QByteArray,
        StdString,
        IStringView
    };

    union {
        QByteArray m_qByteArray;
        std::string m_stdString;
        IStringView m_iStringView;
    };

    Type m_type{Type::Invalid};

public:
    IStringData();
    ~IStringData();
    IStringData(const IStringData& other);
    IStringData(IStringData&& other) noexcept;
    IStringData& operator=(const IStringData& other);
    IStringData& operator=(IStringData&& other) noexcept;

    IStringData(const QByteArray& byteArray);
    IStringData(QByteArray&& byteArray) noexcept;
    IStringData(const std::string& stdString);
    IStringData(std::string&& stdString) noexcept;
    IStringData(IStringView stringView);


    IStringData& operator=(const QByteArray& byteArray);
    IStringData& operator=(QByteArray&& byteArray) noexcept;
    IStringData& operator=(const std::string& stdString);
    IStringData& operator=(std::string&& stdString) noexcept;
    IStringData& operator=(IStringView stringView);
    IStringData& operator=(std::nullptr_t);

public:
    IStringView toStringView() const;

private:
    void clear();
    void copyFrom(const IStringData& other);
    void moveFrom(IStringData&& other) noexcept;
};

$PackageWebCoreEnd
