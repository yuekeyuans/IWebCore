#pragma once

#include "IHttpAction.h"

$PackageWebCoreBegin

template<typename T, bool recyclable = false>
class IHttpActionInterface : public IHttpAction
{
public:
    IHttpActionInterface() = default;

public:
    static T* instance();
};

template<typename T, bool recyclable>
T* IHttpActionInterface<T, recyclable>::instance()
{
    if constexpr (recyclable){
        qFatal("this method must not be used when action is recylable");
    }

    static T t{};
    return &t;
}

$PackageWebCoreEnd
