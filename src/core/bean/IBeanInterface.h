#pragma once

#include "IBeanWare.h"
#include "IBeanAbort.h"
#include "IBeanTypeManage.h"
#include "IBeanPreProcessor.h"
#include "IBeanRegisterTypeUnit.h"
#include "IBeanTraitInterface.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ITraceUnit.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true, typename U=IBeanDefaultTrait>
class IBeanInterface : protected IBeanWare, public ITaskInstantUnit<T, enabled>, protected U, private IBeanRegisterTypeUnit<T>
{
public:
    static inline constexpr bool IS_USE_EXCEPTION = U::ERROR_HANDLE_TYPE == IBeanDefaultTrait::ErrorHandleType::Exception;

public:
    IBeanInterface() = default;

public:
    virtual IJson toJson() const final;
    virtual bool loadJson(const IJson &value) final;

private:
    int getMetaTypeId() const;
    const QVector<QMetaMethod>& getMetaMethods() const;
    const QMap<QString, QString>& getMetaClassInfos() const;
    const std::vector<QMetaProperty>& getMetaProperties() const;
    const QMetaMethod& getMetaMethod(const QString &name) const;
//    const QMetaProperty& getMetaProperty(const QString& name) const;
//    virtual QVariant getFieldValue(const QString& name) const final;
//    virtual void setFieldValue(const QString& name, const QVariant& value) final;

private:
    virtual void $task() final;
};

template<typename T, bool enabled, typename U>
IJson IBeanInterface<T, enabled, U>::toJson() const
{
    static std::map<const char*, const QMetaMethod*> methodPair;
    static std::once_flag flag;
    std::call_once(flag, [this](){
        const auto& props = getMetaProperties();
        for(const auto& prop : props){
            const auto& method = getMetaMethod("$" + QString(prop.name()) + "_toJsonValue");
            if(!method.isValid()){
                IBeanAbort::abortToJsonMethodNotExist(prop.name(), $ISourceLocation);
            }
            methodPair[prop.name()] = &method;
        }
    });

    IJson obj = IJson::object();
    for(const auto& [key, method] : methodPair){
        IJson json;
        method->invokeOnGadget(const_cast<void*>(static_cast<const void*>(this)), Q_RETURN_ARG(IJson, json));
        obj[key] = std::move(json);
    }
    return obj;
}

template<typename T, bool enabled, typename U>
bool IBeanInterface<T, enabled, U>::loadJson(const IJson &value)
{
    static std::map<std::string, const QMetaMethod*> methodPair;
    static std::once_flag flag;
    std::call_once(flag, [this](){
        const auto& props = getMetaProperties();
        for(const auto& prop : props){
            const auto& method = getMetaMethod("$" + QString(prop.name()) + "_fromJsonValue");
            if(!method.isValid()){
                IBeanAbort::abortLoadJsonMethodNotExist(prop.name(), $ISourceLocation);
            }
            methodPair[prop.name()] = &method;
        }
    });

    for(const auto& [key, method] : methodPair){
        if(value.contains(key)){
            auto val = value[key];
            bool ok;
            method->invokeOnGadget(const_cast<void*>(static_cast<const void*>(this)),Q_RETURN_ARG(bool, ok), Q_ARG(IJson, val));
            if(!ok){
                return false;
            }
        }
    }
    return true;
}

template<typename T, bool enabled, typename U>
int IBeanInterface<T, enabled, U>::getMetaTypeId() const
{
    static int id = qMetaTypeId<T>();
    return id;
}

template<typename T, bool enabled, typename U>
const QVector<QMetaMethod>& IBeanInterface<T, enabled, U>::getMetaMethods() const
{
    static auto methods =  IMetaUtil::getMetaMethods(T::staticMetaObject);
    return methods;
}

template<typename T, bool enabled, typename U>
const QMap<QString, QString>& IBeanInterface<T, enabled, U>::getMetaClassInfos() const
{
    static auto clsInfos = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    return clsInfos;
}

template<typename T, bool enabled, typename U>
const std::vector<QMetaProperty>& IBeanInterface<T, enabled, U>::getMetaProperties() const
{
    static auto properties = IMetaUtil::getMetaProperties(T::staticMetaObject);
    return properties;
}

template<typename T, bool enabled, typename U>
const QMetaMethod& IBeanInterface<T, enabled, U>::getMetaMethod(const QString &name) const
{
    const auto& methods = getMetaMethods();
    for(const QMetaMethod& method : methods){
        if(method.name() == name){
            return method;
        }
    }

    static QMetaMethod s_emptyMethod{};
    return s_emptyMethod;
}

//template<typename T, bool enabled, typename U>
//const QMetaProperty& IBeanInterface<T, enabled, U>::getMetaProperty(const QString& name) const
//{
//    const auto props = getMetaProperties();
//    for(const QMetaProperty& prop : props){
//        if(prop.name() == name){
//            return prop;
//        }
//    }

//    static QMetaProperty s_prop{};
//    return s_prop;
//}

//template<typename T, bool enabled, typename U>
//QVariant IBeanInterface<T, enabled, U>::getFieldValue(const QString& name) const
//{
//    const auto& property = getMetaProperty(name);
//    return IMetaUtil::readProperty(property, this);
//}

//template<typename T, bool enabled, typename U>
//void IBeanInterface<T, enabled, U>::setFieldValue(const QString& name, const QVariant& value)
//{
//    const auto& property = getMetaProperty(name);
//    IMetaUtil::writeProperty(property, this, value);
//}

template<typename T, bool enabled, typename U>
void IBeanInterface<T, enabled, U>::$task()
{
    if constexpr (enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IBeanRegisterTypeUnit::registType();
        });
    }
}
$PackageWebCoreEnd
