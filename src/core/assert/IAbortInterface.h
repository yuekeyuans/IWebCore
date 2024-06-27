#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/assert/IAbortPreProcessor.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

struct ISourceLocation
{
    const char* filename{nullptr};
    const char* function{nullptr};
    int line{0};
};

#define $ISourceLocation ISourceLocation{__FILE__, __FUNCTION__, __LINE__}

template<typename T>
class IAbortInterface : public ISingletonUnit<T>
{
public:
    IAbortInterface() = default;

protected:
    void abort(int code, const QString& description, ISourceLocation location);
    void abort(int code, ISourceLocation location);
    virtual QMap<int, QString> getAbortDescription() const = 0;
    virtual QString extraInfo(){ return {};}        // 这个是用于提供对于此类型注解的公共信息

private:
    void checkAbortInfoLength();
};

template<typename T>
void IAbortInterface<T>::abort(int code, ISourceLocation location)
{
    return abort(code, {}, location);
}

template<typename T>
void IAbortInterface<T>::abort(int code, const QString& description, ISourceLocation location)
{
    checkAbortInfoLength();
    QStringList tips;
    auto infos = getAbortDescription();
    if(infos.contains(code)){
        tips.append("ABORT: " + infos[code]);
    }else{
        qFatal("this should not exist!!!");
    }

    if(!description.isEmpty()){
        tips.append("DESCRIPTON: " + description);
    }
    if(location.line){
        tips.append("SOURCE_LOCATION: FILE " + QString::fromLocal8Bit(location.filename)
                    + " FUNCTION " + QString::fromLocal8Bit(location.function)
                    + " LINE " + QString::number(location.line));
    }
    qFatal(tips.join("\n").toUtf8());
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
