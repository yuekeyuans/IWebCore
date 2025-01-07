#pragma once

#include "core/util/IPackageUtil.h"
#include <string_view>
#include <QString>
#include <QByteArray>
#include "asio.hpp"

$PackageWebCoreBegin

class IStringViewList;
class IStringView : public std::string_view
{
public:
    IStringView() = default;
    IStringView(const std::string& data);
    IStringView(const QByteArray& data);
    IStringView(std::string_view data);
    IStringView(const char* data);
    IStringView(const char* data, std::size_t length);
    IStringView(const IStringView& data);

    operator QByteArray() const;
    bool operator ==(const char*) const;
    bool operator ==(const IStringView&) const;
    bool operator !=(const IStringView&) const;
    bool operator <(IStringView) const;

public:
    static uint qHash(const IWebCore::IStringView *obj, uint seed = 0);

public:
    QString toQString() const;
    std::string toStdString() const;
    QByteArray toQByteArray() const;
    asio::const_buffer toAsioBuffer() const;

    IStringView substr(const size_type _Off, size_type _Count=std::string::npos) const;
    IStringView trimmed();
    IStringViewList split(char) const;
    IStringViewList split(IStringView) const;
    bool startWith(IStringView prefix) const;
    bool endWith(IStringView suffix) const;
    bool equalIgnoreCase(IStringView) const;
    bool containIgnoreCase(IStringView) const;

public:
    template<typename T>
    T value(bool& ok) const;
};

class IStringViewList : public QList<IStringView>
{
public:
    IStringViewList() = default;
    IStringViewList(QList<IStringView> data);

public:
    std::string join(IStringView);
};

$PackageWebCoreEnd

template<>
inline uint qHash<IWebCore::IStringView>(const IWebCore::IStringView *obj, uint seed)
{
    return IWebCore::IStringView::qHash(obj, seed);
}

template<>
inline uint qHash<IWebCore::IStringView>(const IWebCore::IStringView &obj, uint seed)
{
    return IWebCore::IStringView::qHash(&obj, seed);
}

namespace std {
    template <>
    struct hash<IWebCore::IStringView> {
        size_t operator()(const IWebCore::IStringView& obj) const {
            return qHash(&obj);
        }
    };
}
