#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IToeUtil
{
    void setOk(bool& ok, bool value);
    void setOk(bool* ok, bool value);

    void setOk(bool condition, bool* ok, bool value);
    void setOk(bool condition, bool& ok, bool value);

    void setOkAnd(bool* ok, bool value);
    void setOkAnd(bool& ok, bool value);

    bool isPrimaryKeyType(QMetaType::Type type);
}

$PackageWebCoreEnd

#include "IToeUtil.cpp"
