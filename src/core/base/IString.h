#pragma once

#include "core/util/IPackageUtil.h"
#include "core/base/IStringView.h"

$PackageWebCoreBegin

struct IString {
private:
    enum class Type {
        IStringView, // default, and empty
        QByteArray,
        StdString,
    };

public:
    IString();
    ~IString();

    IString(const IString& other);
    IString(IString&& other) noexcept;
    IString& operator=(const IString& other);
    IString& operator=(IString&& other) noexcept;

    IString(const IString*);
    IString(const std::string*);
    IString(const QByteArray*);

    IString(const char*);
    IString(const QByteArray& byteArray);
    IString(QByteArray&& byteArray) noexcept;
    IString(const std::string& stdString);
    IString(std::string&& stdString) noexcept;
    IString(IStringView stringView);

    IString& operator=(const IString*);
    IString& operator=(const QByteArray*);
    IString& operator=(const std::string*);

    IString& operator=(const char*);
    IString& operator=(const QString&);
    IString& operator=(const QByteArray& byteArray);
    IString& operator=(QByteArray&& byteArray) noexcept;
    IString& operator=(const std::string& stdString);
    IString& operator=(std::string&& stdString) noexcept;
    IString& operator=(IStringView stringView);
    IString& operator=(std::nullptr_t);
    bool operator ==(const IString&) const;
    bool operator <(const IString&) const;

public:
    bool isSolid() const;
    bool isEmpty() const;
    IString& solidify();
    operator bool() const;
    operator IStringView() const;

public:
    IStringViewList split(char) const;
    IStringViewList split(const IString&) const;

private:
    void clear();
    void copyFrom(const IString& other);
    void moveFrom(IString&& other) noexcept;

private:
    union {
        QByteArray m_qByteArray;
        std::string m_stdString;
    };

    Type m_type{Type::IStringView};

public:
    IStringView m_stringView{};
};

// TODO: 之后详细定义
using IStringList = QList<IString>;

$PackageWebCoreEnd

namespace std {
    template <>
    struct hash<IString> {
        std::size_t operator()(const IString& key) const noexcept {
            return std::hash<std::string_view>()(key.m_stringView);
        }
    };
}
