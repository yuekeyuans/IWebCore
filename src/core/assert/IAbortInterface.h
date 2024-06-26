#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/assert/IAbortPreProcessor.h"
#include "core/base/IMetaUtil.h"

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
    virtual QMap<int, QString> getAbortDescription() const = 0;

private:
    void checkAbortInfoLength();
};

template<typename T>
void IAbortInterface<T>::abort(int code)
{
    checkAbortInfoLength();
    auto infos = getAbortDescription();
    if(infos.contains(code)){
        qFatal(infos[code].toUtf8());
    }else{
        qFatal("not found");
    }
}

template<typename T>
void IAbortInterface<T>::checkAbortInfoLength()
{
    static std::once_flag flag;
    std::call_once(flag, [](){
        if((int)T::EndTag != T::instance()->getAbortDescription().size()){
            QString info = "Abort tag count and abort description count mismatch, please add abort description. Abort at ";
            info.append(IMetaUtil::getTypename<T>());
            qFatal(info.toUtf8());
        }
    });
}

$PackageWebCoreEnd
