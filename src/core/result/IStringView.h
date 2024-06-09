#pragma once

#include "core/base/IPackageUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include <string_view>
#include <QString>
#include <QByteArray>
#include <functional>

$PackageWebCoreBegin

class IStringView : public std::string_view, private IRegisterMetaTypeUnit<IStringView>
{
    using std::string_view::basic_string_view;
public:
    IStringView() = default;
    IStringView(const std::string& data);
    IStringView(const QByteArray& data);
    IStringView(std::string_view data);

public:
    static uint qHash(const IWebCore::IStringView *obj, uint seed = 0);

public:
    QString toQString() const;
    QByteArray toQByteArray() const;
    IStringView substr(const size_type _Off, size_type _Count=std::string::npos) const;
    IStringView trimmed();
    QList<IStringView> split(char) const;
    bool startWith(IStringView prefix);
    bool endWith(IStringView suffix);

};


using IStringViewList = QList<IStringView>;


Q_DECLARE_METATYPE(IStringView)


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
