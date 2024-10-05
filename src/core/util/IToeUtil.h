﻿#pragma once

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

//    void setOkOr(bool* ok, bool value);
//    void setOkOr(bool& ok, bool value);

//    void setOkXor(bool* ok, bool value);
//    void setOkXor(bool& ok, bool value);

    bool isPrimaryKeyType(QMetaType::Type type);

//    bool isFalsy(const QString& value);
//    bool isTruthy(const QString& value);

//    QString trimQuote(const QString& content);
}

$PackageWebCoreEnd

#include "IToeUtil.cpp"
