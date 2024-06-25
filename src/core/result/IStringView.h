#pragma once

#include "core/base/IPackageUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include <string_view>
#include <QString>
#include <QByteArray>
#include <functional>

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
    IStringView(const IStringView& data);

    operator QByteArray();
    bool operator ==(const char*);
    bool operator ==(IStringView);
    bool operator <(IStringView);

public:
    static uint qHash(const IWebCore::IStringView *obj, uint seed = 0);

    // TODO: 这个将来要对用户隐藏，因为搞不好，这个东西会膨胀，耗费内存
    static IStringView stash(const std::string& data);
    static IStringView stash(const QByteArray& data);
    static IStringView stash(const char* data);

public:
    QString toQString() const;
    QByteArray toQByteArray() const;
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


class IStringViewStash
{
public:
    IStringView stash(QByteArray data);

private:
    QMutex m_mutex;
    std::list<QByteArray> m_stashed;
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
