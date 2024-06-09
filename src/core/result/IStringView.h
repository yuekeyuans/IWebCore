#pragma once

#include "core/base/IPackageUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include <string_view>
#include <QString>
#include <QByteArray>

$PackageWebCoreBegin

class IStringView : public std::string_view, private IRegisterMetaTypeUnit<IStringView>
{
    using std::string_view::basic_string_view;
public:
    IStringView(const std::string& data);
    IStringView(const QByteArray& data);
    IStringView(std::string_view data);


public:
    QString toQString() const;
    QByteArray toQByteArray() const;
    IStringView substr(const size_type _Off, size_type _Count) const;

    QList<IStringView> split(char);

//    IStringView trimmed();
//    bool startWith(const QString&);
//    bool endWith(const QString&);
};

Q_DECLARE_METATYPE(IStringView)

$PackageWebCoreEnd
