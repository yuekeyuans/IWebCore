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
            auto type = field.type();
            if(type >= QMetaType::User && type != stdStringId){
                obj[field.name()] = toJsonValueOfBeanType(this, field, ok);
            }else{
                auto value = field.readOnGadget(this);
                obj[field.name()] = toJsonValueOfPlainType(type, value, ok);
            }

        }
        return obj;
    }

    virtual bool loadJson(const IJson &value)
    {
        if(!value.is_object()){
            return false;
        }

        bool ok{true};
        const auto& fields = getMetaProperties();
        for(const QMetaProperty& field :fields){
            auto type = field.type();
            if(type >= QMetaType::User){
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

    IJson toJsonValueOfPlainType(int type, const QVariant &value, bool* ok) const
    {
        static auto stdStringId = qMetaTypeId<std::string>();
        if(stdStringId == type){
            return value.value<std::string>();
        }

        switch (type) {
        case QMetaType::Bool:
            return  value.toBool();
            break;
        case QMetaType::UChar:
        case QMetaType::Char:
        case QMetaType::SChar:
        case QMetaType::Short:
        case QMetaType::UShort:
        case QMetaType::UInt:
        case QMetaType::Int:
        case QMetaType::Long:
            return  value.toLongLong(ok);
            break;
        case QMetaType::ULong:
        case QMetaType::ULongLong:
            // TODO: 这里需要验证
            return  value.toLongLong(ok);
            break;
        case QMetaType::Float:
            return  value.toFloat(ok);
            break;
        case QMetaType::Double:
            return  value.toDouble(ok);
            break;
        case QMetaType::QString:
            return  value.toString().toStdString();
            break;

//        case QMetaType::QStringList:{
//            QJsonArray array;
//            auto strlist = value.toStringList();
//            for(const auto& str : strlist){
//                array.append(str);
//            }
//            return  array;
//        }
//            break;
//        case QMetaType::QByteArray:
//            return  QString(value.toByteArray());
//            break;
//        case QMetaType::QJsonArray:
//            return  value.toJsonArray();
//            break;
//        case QMetaType::QJsonObject:
//            return  value.toJsonObject();
//            break;
//        case QMetaType::QJsonValue:
//            return  value.toJsonValue();
//            break;
        default:
            ok = false;
            return {};
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

    // TODO: 一定要吧 Json 库给换掉，太恶心了。
    bool loadJsonValueOfPlainType(const void *handle, const QMetaProperty &prop, const IJson &value)
    {
        bool ok{true};
        auto type = prop.type();
        switch (type) {
        case QMetaType::Bool:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<bool>());
            break;
        case QMetaType::UChar:
        case QMetaType::Char:
        case QMetaType::SChar:
        case QMetaType::UShort:
        case QMetaType::Short:
        case QMetaType::Int:
        case QMetaType::UInt:
        case QMetaType::Long:
        case QMetaType::ULong:
        case QMetaType::LongLong:
        case QMetaType::ULongLong:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<int>());
            break;
        case QMetaType::Float:
        case QMetaType::Double:
            prop.writeOnGadget(const_cast<void*>(handle), value.get<double>());
            break;
        case QMetaType::QString:
            prop.writeOnGadget(const_cast<void*>(handle), QString::fromStdString(value.get<std::string>()));
            break;
//        case QMetaType::QStringList:
//        {
//            QStringList ret;
//            auto array = value.toArray();
//            for(auto val : array){
//                ret.append(val.toString());
//            }
//            prop.writeOnGadget(const_cast<void*>(handle), ret);
//        }
//        case QMetaType::QByteArray:
//            prop.writeOnGadget(const_cast<void*>(handle), value.toString().toUtf8());
//            break;
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
            auto id = qMetaTypeId<T>();
            IMetaUtil::registerMetaType<T>();
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
