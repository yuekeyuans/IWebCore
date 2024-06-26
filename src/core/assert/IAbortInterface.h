#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/assert/IAbortPreProcessor.h"

$PackageWebCoreBegin

struct ISourceLocation
{
    const char* filename;
    const char* function;
    int line;
};

template<typename T>
class IAbortInterface : public ISingletonUnit<T>
{
public:
    IAbortInterface() = default;

public:
    void abort(int code);
    virtual QMap<int, QString> getAbortInfo() const = 0;
};

template<typename T>
void IAbortInterface<T>::abort(int code)
{
    auto infos = getAbortInfo();
    if(infos.contains(code)){
        qFatal(infos[code].toUtf8());
    }else{
        qFatal("not found");
    }
}

$PackageWebCoreEnd
