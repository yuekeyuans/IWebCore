#pragma once

#include "IAssertManage.h"
#include "base/IHeaderUtil.h"
#include "base/IJsonUtil.h"
#include "core/unit/IRegisterInstanceUnit.h"

$PackageWebCoreBegin

extern const char FatalType[];
extern const char WarningType[];

template<typename T, bool enabled = true, const char* type = FatalType>
class IAssertJsonInterface : public IRegisterInstanceUnit<T, enabled>
{
public:
    IAssertJsonInterface() = default;
    virtual ~IAssertJsonInterface() = default;

    virtual QString getAssertInfo() = 0;

public:
    virtual void registerToBase() override;
};


template<typename T, bool enabled, const char *type>
void IAssertJsonInterface<T, enabled, type>::registerToBase() {
    auto inst = T::instance();

    bool convertOk;
    QString json = inst->getAssertInfo();
    QJsonArray array = IJsonUtil::toJsonArray(json, &convertOk);
    if(!convertOk){
        qFatal("error with IAssertJsonInterface");
    }

    for(QJsonValue val : array){
        QJsonObject obj = val.toObject();

        IAssertInfo info;
        info.key = obj["key"].toString();
        info.reason = obj["reason"].toString();
        info.solution = obj["solution"].toString();
        info.description = obj["description"].toString();

        if(type == FatalType){
            IAssertManage::registerFatalInfo(info);
        }else{
            IAssertManage::registerWarnInfo(info);
        }
    }
}

template<typename T, bool enabled = true>
using IFatalAssertJsonInterface = IAssertJsonInterface<T, enabled, FatalType>;

template<typename T, bool enabled = true>
using IWarnAssertJsonInterface = IAssertJsonInterface<T, enabled, WarningType>;


$PackageWebCoreEnd
