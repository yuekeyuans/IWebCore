#pragma once
#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

namespace IToeUtil
{
    void setOk(bool* ok, bool value);
    void setOk(bool condition, bool* ok, bool value);
    void setOkAnd(bool *ok, bool value);

    bool isPrimaryKeyType(QMetaType::Type type);

    bool isFalsy(const QString& value);
    bool isTruthy(const QString& value);

    template<typename T>
    void deletePointer(T* ptr);

    template<typename T, int N>
    void deletePointer(T ptr[N]);

    QString trimQuote(const QString& content);
};

template<typename T>
void IToeUtil::deletePointer(T *ptr)
{
    if(ptr != nullptr){
        delete ptr;
        ptr = nullptr;
    }
}

template<typename T, int N>
void IToeUtil::deletePointer(T ptr[N] )
{
    if(ptr != nullptr){
        delete [] ptr;
        ptr = nullptr;
    }
}

$PackageWebCoreEnd
