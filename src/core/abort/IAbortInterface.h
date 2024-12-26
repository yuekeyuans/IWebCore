#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "core/abort/IAbortPreProcessor.h"
#include "core/util/IMetaUtil.h"

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
    void abort(int code, const char* data, const QString& description, ISourceLocation location);
    void abort(int code, const char* data, ISourceLocation location);
    QString abortClass();
    virtual QMap<int, QString> abortDescription() const = 0;
    virtual QString abortComment() { return {}; }       // 这个是用于提供对于此类型注解的公共信息

private:
    void checkAbortInfoLength();
};

template<typename T>
void IAbortInterface<T>::abort(int code, const char* data, ISourceLocation location)
{
    return abort(code, data, {}, location);
}

template<typename T>
void IAbortInterface<T>::abort(int code, const char* data, const QString& description, ISourceLocation location)
{
    checkAbortInfoLength();
    QStringList tips;
    tips.append(QString("NAME: ").append(data));

    auto infos = abortDescription();

    if(infos.contains(code) && !infos[code].isEmpty()){
        tips.append("ABORT: " + infos[code]);
    }
    tips.append("ABORT CLASS: " + abortClass());
    if(!abortComment().isEmpty()){
        tips.append("ABORT COMMENT: " + abortComment());
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
QString IAbortInterface<T>::abortClass()
{
    return QString::fromStdString(IMetaUtil::getBareTypeName<T>()); // TODO: fix latter
}

template<typename T>
void IAbortInterface<T>::checkAbortInfoLength()
{
    static std::once_flag flag;
    std::call_once(flag, [](){
        if((int)T::EndTag != T::instance()->abortDescription().size()){
            QString info = "Abort tag count and abort description count mismatch, please add abort description. Abort at ";
            info.append(QString::fromStdString(IMetaUtil::getBareTypeName<T>()));
            qFatal(info.toUtf8());
        }
    });
}

$PackageWebCoreEnd
