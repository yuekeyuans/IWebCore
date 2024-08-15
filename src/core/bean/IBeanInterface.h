#pragma once

#include "IBeanWare.h"
#include "IBeanTypeManage.h"
#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/unit/ITraceUnit.h"
#include "core/bean/IBeanPreProcessor.h"
#include "core/task/unit/ITaskInstantUnit.h"

$PackageWebCoreBegin

template<class T, bool enabled = true>
class IBeanInterface : public IBeanWare, public ITaskInstantUnit<T, enabled>, public ITraceUnit<T, true>
{
public:
    IBeanInterface() = default;
    virtual ~IBeanInterface() = default;

public:
    virtual const QString& className() const final {
        static const QString clsName = T::staticMetaObject.className();
        return clsName;
    }
    virtual QMetaObject getMetaObject() const final{
        return T::staticMetaObject;
    }
    virtual int getMetaTypeId() const{
        return qMetaTypeId<T>();
    }
    virtual QMetaMethod getMetaMethod(const QString &name) const final {
        const auto& methods = getMetaMethods();
        for(const QMetaMethod& method : methods){
            if(method.name() == name){
                return method;
            }
        }
        return {};
    }
    virtual const QVector<QMetaMethod>& getMetaMethods() const final{
        static auto methods =  IMetaUtil::getMetaMethods(T::staticMetaObject);
        return methods;
    }
    virtual const QMap<QString, QString>& getMetaClassInfos() const final{
        static auto clsInfos = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
        return clsInfos;
    }
    virtual QMetaProperty getMetaProperty(const QString& name) const final {
        return IMetaUtil::getMetaPropertyByName(T::staticMetaObject, name);
    }
    virtual const QVector<QMetaProperty>& getMetaProperties() const final {
        static auto props = IMetaUtil::getMetaProperties(T::staticMetaObject);
        return props;
    }
    virtual QVariant getFieldValue(const QString& name) const final {
        const auto& property = getMetaProperty(name);
        return IMetaUtil::readProperty(property, this);
    }
    virtual void setFieldValue(const QString& name, const QVariant& value) final{
        const auto& property = getMetaProperty(name);
        IMetaUtil::writeProperty(property, this, value);
    }
    virtual const QStringList& getIgnorableFieldNames() const override{
        static QStringList ignoredFields = IMetaUtil::getIgnoredFields(T::staticMetaObject);
        return ignoredFields;
    }
    virtual const QVector<int>& getIgnorableFieldIndexes() const override{
        static QVector<int> ignoredFields = IMetaUtil::getIgnoredFieldIndexes(T::staticMetaObject);
        return ignoredFields;
    }
    virtual bool isIgnorableField(const QString& name) const override{
        static const QStringList ignoredFields = getIgnorableFieldNames();
        return ignoredFields.contains(name);
    }
    virtual bool isIgnorableField(int index) const override{
        static const QVector<int> ignoredFields = getIgnorableFieldIndexes();
        return ignoredFields.contains(index);
    }
    virtual const QStringList& getMetaFieldNames() const override{
        static QStringList fieldNames = IMetaUtil::getMetaPropertyNames(T::staticMetaObject);
        return fieldNames;
    }

public:
    virtual QString name() const;
    virtual void task() final;
};

template <typename T, bool enabled>
QString IBeanInterface<T, enabled>::name() const
{
    return IMetaUtil::getTypename<T>();
}

template<typename T, bool enabled>
void IBeanInterface<T, enabled>::task()
{
    if constexpr (enabled){
        static std::once_flag initRegisterFlag;
        std::call_once(initRegisterFlag, [](){
            IMetaUtil::registerMetaType<T>();
            IBeanTypeManage::registerBeanType(typeid (T).name());   // register type
            auto id = qMetaTypeId<T>();
            IBeanTypeManage::instance()->registerToJsonFun(id, [](void* ptr, bool* ok)->QJsonValue{
                return static_cast<T*>(ptr)->toJson(ok);
            });
            IBeanTypeManage::instance()->registerLoadJsonFun(id, [](void* ptr, const QJsonValue& json)->bool{
                return static_cast<T*>(ptr)->loadJson(json);
            });
        });
    }
}
$PackageWebCoreEnd
