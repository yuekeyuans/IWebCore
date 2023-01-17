#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IToeUtil
{
    void setOk(bool* ok, bool value);
    void setOk(bool& ok, bool value);

    void setOk(bool condition, bool* ok, bool value);
    void setOk(bool condition, bool& ok, bool value);

    void setOkAnd(bool* ok, bool value);
    void setOkAnd(bool& ok, bool value);

    void setOkOr(bool* ok, bool value);
    void setOkOr(bool& ok, bool value);

    void setOkXor(bool* ok, bool value);
    void setOkXor(bool& ok, bool value);

    bool isPrimaryKeyType(QMetaType::Type type);

    bool isFalsy(const QString& value);
    bool isTruthy(const QString& value);

    QString trimQuote(const QString& content);
};

inline void IToeUtil::setOk(bool &ok, bool value)
{
    ok = value;
}

inline void IToeUtil::setOk(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok = value;
    }
}

inline void IToeUtil::setOk(bool condition, bool *ok, bool value)
{
    if(condition){
        if(ok != nullptr){
            *ok = value;
        }
    }
}

inline void IToeUtil::setOk(bool condition, bool &ok, bool value)
{
    if(condition){
        ok = value;
    }
}

inline void IToeUtil::setOkAnd(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok &= value;
    }
}


inline void IToeUtil::setOkAnd(bool &ok, bool value)
{
    ok &= value;
}


inline void IToeUtil::setOkOr(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok |= value;
    }
}

inline void IToeUtil::setOkOr(bool &ok, bool value)
{
    ok |= value;
}

inline void IToeUtil::setOkXor(bool *ok, bool value)
{
    if(ok != nullptr){
        *ok ^= value;
    }
}

inline void IToeUtil::setOkXor(bool &ok, bool value)
{
    ok ^= value;
}


$PackageWebCoreEnd
