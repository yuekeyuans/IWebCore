#pragma once

#include "IBeanWare.h"
#include "IBeanTypeManage.h"
#include "IBeanPreProcessor.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ITraceUnit.h"
#include "core/task/unit/ITaskInstantUnit.h"
#include "IJson.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IBeanInterface : public IBeanWare, public ITaskInstantUnit<T, enabled>, public ITraceUnit<T, false>
{
    template<typename U, bool>
    friend class ITaskIstantUnit;
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    const QString& className() const {
        static const QString clsName = IMetaUtil::getTypename<T>();
        return clsName;
    }

    int getMetaTypeId() const {
        return qMetaTypeId<T>();
    }

    const QVector<QMetaMethod>& getMetaMethods() const {
        static auto methods =  IMetaUtil::getMetaMethods(T::staticMetaObject);
        return methods;
    }

    const QMap<QString, QString>& getMetaClassInfos() const {
        static auto clsInfos = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
        return clsInfos;
    }
    const QVector<QMetaProperty>& getMetaProperties() const {
        static auto props = IMetaUtil::getMetaProperties(T::staticMetaObject);
        return props;
    }

    QMetaMethod getMetaMethod(const QString &name) const {
        const auto& methods = getMetaMethods();
        for(const QMetaMethod& method : methods){
            if(method.name() == name){
                return method;
            }
        }
        return {};
    }

    QMetaProperty getMetaProperty(const QString& name) const {
        return IMetaUtil::getMetaPropertyByName(T::staticMetaObject, name);
    }

    virtual QVariant getFieldValue(const QString& name) const final {
        const auto& property = getMetaProperty(name);
        return IMetaUtil::readProperty(property, this);
    }

    virtual void setFieldValue(const QString& name, const QVariant& value) final{
        const auto& property = getMetaProperty(name);
        IMetaUtil::writeProperty(property, this, value);
    }
    virtual const QStringList& getIgnorableFieldNames() const{
        static QStringList ignoredFields = IMetaUtil::getIgnoredFields(T::staticMetaObject);
        return ignoredFields;
    }
    virtual const QVector<int>& getIgnorableFieldIndexes() const{
        static QVector<int> ignoredFields = IMetaUtil::getIgnoredFieldIndexes(T::staticMetaObject);
        return ignoredFields;
    }
    virtual bool isIgnorableField(const QString& name) const{
        static const QStringList ignoredFields = getIgnorableFieldNames();
        return ignoredFields.contains(name);
    }
    virtual bool isIgnorableField(int index) const{
        static const QVector<int> ignoredFields = getIgnorableFieldIndexes();
        return ignoredFields.contains(index);
    }
    virtual const QStringList& getMetaFieldNames() const{
        static QStringList fieldNames = IMetaUtil::getMetaPropertyNames(T::staticMetaObject);
        return fieldNames;
    }

public:
    virtual IJson toJson(bool *ok) const
    {
        static auto stdStringId = qMetaTypeId<std::string>();

        IJson obj;
        const auto& fields = getMetaProperties();
        for(const QMetaProperty& field : fields){
            auto type = field.userType();
            if(type == stdStringId){
                auto value = field.readOnGadget(this);
                obj[field.name()] = value.value<std::string>();
            }else if(type >= QMetaType::User){
                if(IBeanTypeManage::instance()->isBeanIdExist(type)){
                    obj[field.name()] = toJsonValueOfBeanType(this, field, ok);
                }else{
                    qDebug() << "This should be Tested" << (int)type << QMetaType::typeName(type) << field.name() << field.typeName();
                }
            }else{
                obj[field.name()] = toJsonValueOfPlainType(type, field, ok);
            }

        }
        return obj;
    }

    virtual bool loadJson(const IJson &value)
    {
        static auto stdStringId = qMetaTypeId<std::string>();
        if(!value.is_object()){
            return false;
        }

        bool ok{true};
        const auto& fields = getMetaProperties();
        for(const QMetaProperty& field :fields){
            if(!value.contains(field.name())){
                qDebug() << "skip field" << field.name();
                continue;
            }
            auto type = field.userType();
            if(type == stdStringId){
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

    IJson toJsonValueOfBeanType(const void *handle, const QMetaProperty& prop, bool* ok) const
    {
        auto getPtrFun = getMetaMethod(QString("$get_") + prop.name() + "_ptr");
        void* ptr{};
        QGenericReturnArgument retVal("void*", &ptr);
        getPtrFun.invokeOnGadget(const_cast<void*>(handle), retVal);
        auto toJsonfun = IBeanTypeManage::instance()->getToJsonFun(getMetaTypeId());
        return toJsonfun(ptr, ok);
    }

    IJson toJsonValueOfPlainType(int type, const QMetaProperty &prop, bool* ok) const
    {
        auto value = prop.readOnGadget(this);

        switch (type) {
        case QMetaType::Bool:
            return  value.toBool();
            break;
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
            break;
        case QMetaType::QString:
            return  value.toString().toStdString();
            break;

        case QMetaType::QStringList:{
            IJson array;
            auto strlist = value.toStringList();
            for(const QString& str : strlist){
                array.push_back(str.toStdString());
            }
            return  array;
        }
        }
        ok = false;
        return {};
    }

    bool loadJsonValueOfBeanType(const void *handle, const QMetaProperty &prop, const IJson &value)
    {
        auto getPtrFun = getMetaMethod(QString("$get_") + prop.name() + "_ptr");
        void* ptr{};
        QGenericReturnArgument retVal("void*", &ptr);
        getPtrFun.invokeOnGadget(const_cast<void*>(handle), retVal);

        auto loadJsonFun = IBeanTypeManage::instance()->getLoadJsonFun(getMetaTypeId());
        return loadJsonFun(ptr, value);
    }

    bool loadJsonValueOfPlainType(void *handle, const QMetaProperty &prop, const IJson &value)
    {
        bool ok{true};
        auto type = prop.type();
        switch (type) {
        case QMetaType::Bool:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<bool>());
            break;
        case QMetaType::UChar:
        case QMetaType::UShort:
        case QMetaType::UInt:
        case QMetaType::ULong:
        case QMetaType::ULongLong:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<uint64_t>());
            break;
        case QMetaType::Char:
        case QMetaType::SChar:
        case QMetaType::Short:
        case QMetaType::Int:
        case QMetaType::Long:
        case QMetaType::LongLong:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<int64_t>());
            break;
        case QMetaType::Float:
        case QMetaType::Double:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<double>());
            break;
        case QMetaType::QString:
            prop.writeOnGadget(const_cast<void*>(handle), QString::fromStdString(value.get<std::string>()));
            break;
        case QMetaType::QStringList:
        {
            QStringList ret;
            for(auto val : value){
                ret.append(QString::fromStdString(val.get<std::string>()));
            }
            prop.writeOnGadget(const_cast<void*>(handle), ret);
        }
        default:
            return false;
        }
        return ok;
    }

private:
    virtual void task() final;
};

template<typename T, bool enabled>
void IBeanInterface<T, enabled>::task()
{
    if constexpr (enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            auto id = IMetaUtil::registerMetaType<T>();
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerToJsonFun(id, [](void* ptr, bool* ok)->IJson{
                return static_cast<T*>(ptr)->toJson(ok);
            });
            IBeanTypeManage::instance()->registerLoadJsonFun(id, [](void* ptr, const IJson& json)->bool{
                return static_cast<T*>(ptr)->loadJson(json);
            });
        });
    }
}
$PackageWebCoreEnd
