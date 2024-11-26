#pragma once

#include "core/util/IPackageUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include <string_view>
#include <QString>
#include <QByteArray>
#include "asio.hpp"

$PackageWebCoreBegin

class IStringViewList;
class IStringView : public std::string_view, private IRegisterMetaTypeUnit<IStringView>
{
    using std::string_view::basic_string_view;
public:
    IStringView() = default;
    IStringView(const std::string& data);
    IStringView(const QByteArray& data);
    IStringView(std::string_view data);
    IStringView(const char* data);
    IStringView(const char* data, std::size_t length);
    IStringView(const IStringView& data);

    operator QByteArray();
    bool operator ==(const char*);
    bool operator ==(IStringView);
    bool operator <(IStringView);

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
};

class IStringViewList : public QList<IStringView>, public IRegisterMetaTypeUnit<IStringViewList>
{
public:
    IStringViewList() = default;
    IStringViewList(QList<IStringView> data);
};


Q_DECLARE_METATYPE(IStringView)
Q_DECLARE_METATYPE(IStringViewList)

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
