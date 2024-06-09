#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

class IStringView : public std::string_view, public IRegisterMetaTypeUnit<IStringView>
{
public:
    using std::string_view::basic_string_view;
};

Q_DECLARE_METATYPE(IStringView)

$PackageWebCoreEnd
