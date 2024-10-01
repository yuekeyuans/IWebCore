#pragma once

#include "IBeanWare.h"
#include "IBeanTypeManage.h"
#include "IBeanPreProcessor.h"
#include "IBeanTraitInterface.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ITraceUnit.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "IJson.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true, typename U=IBeanDefaultTrait>
class IBeanInterface : public IBeanWare, public ITaskInstantUnit<T, enabled>, /*public ITraceUnit<T, false>,*/ protected U
{
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    int getMetaTypeId() const;
    const QVector<QMetaMethod>& getMetaMethods() const;
    const QMap<QString, QString>& getMetaClassInfos() const;
    const std::vector<QMetaProperty>& getMetaProperties() const;
    const QMetaMethod& getMetaMethod(const QString &name) const;
    const QMetaProperty& getMetaProperty(const QString& name) const;
    virtual QVariant getFieldValue(const QString& name) const final;
    virtual void setFieldValue(const QString& name, const QVariant& value) final;

public:
    IJson toJson() const;

//    virtual IJson toJson(bool *ok) const;
    virtual bool loadJson(const IJson &value);

private:
    IJson toJsonValueOfBeanType(const void *handle, const QMetaProperty& prop, bool* ok) const;
    bool loadJsonValueOfBeanType(const void *handle, const QMetaProperty &prop, const IJson &value);

    IJson toJsonValueOfPlainType(int type, const QMetaProperty &prop, bool* ok) const;
    bool loadJsonValueOfPlainType(void *handle, const QMetaProperty &prop, const IJson &value);

private:
    virtual void task() final;
};

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

template<typename T, bool enabled, typename U>
const QMetaProperty& IBeanInterface<T, enabled, U>::getMetaProperty(const QString& name) const
{
    const auto props = getMetaProperties();
    for(const QMetaProperty& prop : props){
        if(prop.name() == name){
            return prop;
        }
    }

    static QMetaProperty s_prop{};
    return s_prop;
}

template<typename T, bool enabled, typename U>
QVariant IBeanInterface<T, enabled, U>::getFieldValue(const QString& name) const
{
    const auto& property = getMetaProperty(name);
    return IMetaUtil::readProperty(property, this);
}

template<typename T, bool enabled, typename U>
void IBeanInterface<T, enabled, U>::setFieldValue(const QString& name, const QVariant& value)
{
    const auto& property = getMetaProperty(name);
    IMetaUtil::writeProperty(property, this, value);
}

template<typename T, bool enabled, typename U>
IJson IBeanInterface<T, enabled, U>::toJson() const
{
    static std::map<const char*, const QMetaMethod*> methodPair;
    static std::once_flag flag;
    std::call_once(flag, [this](){
        const auto& props = getMetaProperties();
        for(const auto& prop : props){
            methodPair[prop.name()] = &getMetaMethod("$" + QString(prop.name()) + "_toJsonValue");
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


//template<typename T, bool enabled, typename U>
//IJson IBeanInterface<T, enabled, U>::toJson(bool *ok) const
//{
//    static auto stdStringId = qMetaTypeId<std::string>();

//    IJson obj = IJson::object();
//    const auto& fields = getMetaProperties();
//    for(const QMetaProperty& field : fields){
//        auto type = field.userType();
//        if(type == stdStringId){
//            auto value = field.readOnGadget(this);
//            obj[field.name()] = value.value<std::string>();
//        }else if(type >= QMetaType::User){
//            if(IBeanTypeManage::instance()->isBeanIdExist(type)){
//                obj[field.name()] = toJsonValueOfBeanType(this, field, ok);
//            }else{
//                qDebug() << "This should be Tested" << (int)type << QMetaType::typeName(type) << field.name() << field.typeName();
//            }
//        }else{
//            obj[field.name()] = toJsonValueOfPlainType(type, field, ok);
//        }

//    }
//    return obj;
//}

template<typename T, bool enabled, typename U>
bool IBeanInterface<T, enabled, U>::loadJson(const IJson &value)
{
    static auto stdStringId = qMetaTypeId<std::string>();
    if(!value.is_object()){
        return false;
    }

    bool ok{true};
    const auto& fields = getMetaProperties();
    for(const QMetaProperty& field :fields){
        if(!value.contains(field.name())){
            continue;
        }

        auto type = field.userType();
        if(type == 0){
            // 处理 std::vector 相关的内容
        } else if(type == stdStringId){
            const std::string val = value[field.name()].get<std::string>();
            field.writeOnGadget(this, QVariant(stdStringId, &val));
        }else if(type >= QMetaType::User){
            loadJsonValueOfBeanType(this, field, value[field.name()]);
        }else{
            loadJsonValueOfPlainType(this, field, value[field.name()]);
        }
    }

    return ok;
}


template<typename T, bool enabled, typename U>
IJson IBeanInterface<T, enabled, U>::toJsonValueOfBeanType(const void *handle, const QMetaProperty& prop, bool* ok) const
{
    const QMetaMethod& getPtrFun = getMetaMethod(QString("$get_") + prop.name() + "_ptr");

    void* ptr{};
    QGenericReturnArgument retVal("void*", &ptr);
    getPtrFun.invokeOnGadget(const_cast<void*>(handle), retVal);
    auto toJsonfun = IBeanTypeManage::instance()->getToJsonFun(getMetaTypeId());
    return toJsonfun(ptr, ok);
}

template<typename T, bool enabled, typename U>
bool IBeanInterface<T, enabled, U>::loadJsonValueOfBeanType(const void *handle, const QMetaProperty &prop, const IJson &value)
{
    const QMetaMethod& getPtrFun = getMetaMethod(QString("$get_") + prop.name() + "_ptr");
    void* ptr{};
    QGenericReturnArgument retVal("void*", &ptr);
    getPtrFun.invokeOnGadget(const_cast<void*>(handle), retVal);

    auto loadJsonFun = IBeanTypeManage::instance()->getLoadJsonFun(getMetaTypeId());
    return loadJsonFun(ptr, value);
}

template<typename T, bool enabled, typename U>
IJson IBeanInterface<T, enabled, U>::toJsonValueOfPlainType(int type, const QMetaProperty &prop, bool* ok) const
{
    auto value = prop.readOnGadget(this);

    switch (type) {
    case QMetaType::Bool:
        return  value.toBool();
    case QMetaType::UChar:
    case QMetaType::UShort:
    case QMetaType::UInt:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
        return value.toULongLong(ok);
    case QMetaType::Char:
    case QMetaType::SChar:
    case QMetaType::Short:
    case QMetaType::Int:
    case QMetaType::Long:
    case QMetaType::LongLong:
        return  value.toLongLong(ok);
    case QMetaType::Float:
    case QMetaType::Double:
        return  value.toDouble(ok);
    case QMetaType::QString:
        return  value.toString().toStdString();
    case QMetaType::QStringList:{
        IJson array;
        auto strlist = value.toStringList();
        for(const QString& str : strlist){
            array.push_back(str.toStdString());
        }
        return  array;
    }
    default:
        return nullptr;
    }
    ok = false;
    return {};
}

template<typename T, bool enabled, typename U>
bool IBeanInterface<T, enabled, U>::loadJsonValueOfPlainType(void *handle, const QMetaProperty &prop, const IJson &value)
{
    auto type = prop.type();
    switch (type) {
    case QMetaType::Bool:
        if(!value.is_boolean()){
            return false;
        }
        prop.writeOnGadget(const_cast<void*>(handle), value.get<bool>());
        break;
    case QMetaType::UChar:
    case QMetaType::UShort:
    case QMetaType::UInt:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
        if(!value.is_number_unsigned()){ return false; }
        prop.writeOnGadget(const_cast<void*>(handle), value.get<uint64_t>());
        break;
    case QMetaType::Char:
    case QMetaType::SChar:
    case QMetaType::Short:
    case QMetaType::Int:
    case QMetaType::Long:
    case QMetaType::LongLong:
        if(!value.is_number_integer()){ return false; }
        prop.writeOnGadget(const_cast<void*>(handle), value.get<int64_t>());
        break;
    case QMetaType::Float:
    case QMetaType::Double:
        if(!value.is_number_float()) { return false; }
        prop.writeOnGadget(const_cast<void*>(handle), value.get<double>());
        break;
    case QMetaType::QString:
        if(!value.is_string()){ return false; }
        prop.writeOnGadget(const_cast<void*>(handle), QString::fromStdString(value.get<std::string>()));
        break;
    case QMetaType::QStringList:
    {
        if(value.is_null()){break;}
        if(!value.is_array()){ return false;}
        QStringList ret;
        for(auto val : value){
            if(!val.is_string()){ return false;}
            ret.append(QString::fromStdString(val.get<std::string>()));
        }
        prop.writeOnGadget(const_cast<void*>(handle), ret);
    }
    default:
        return false;
    }
    return true;
}

template<typename T, bool enabled, typename U>
void IBeanInterface<T, enabled, U>::task()
{
    if constexpr (enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            auto id = IMetaUtil::registerMetaType<T>();
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerBeanProperties(id, IMetaUtil::getMetaProperties(T::staticMetaObject));
//            IBeanTypeManage::instance()->registerToJsonFun(id, [](void* ptr, bool* ok)->IJson{
//                return static_cast<T*>(ptr)->toJson(/*ok*/);    // TODO: check it latter
//            });
            IBeanTypeManage::instance()->registerLoadJsonFun(id, [](void* ptr, const IJson& json)->bool{
                return static_cast<T*>(ptr)->loadJson(json);
            });
        });
    }
}
$PackageWebCoreEnd
