#pragma once

#include "core/util/IPreProcessorUtil.h"

#define $_UseGadget(klassName)   \
public:\
    virtual const QString& className() const final {    \
        static const QString clsName = staticMetaObject.className();    \
        return clsName; \
    }   \
    virtual QMetaObject getMetaObject() const final{    \
        return staticMetaObject;    \
    }   \
    virtual const QVector<QMetaMethod>& getMetaMethods() const final{  \
        static auto methods =  IMetaUtil::getMetaMethods(staticMetaObject); \
        return methods; \
    }   \
    virtual const QMap<QString, QString>& getMetaClassInfos() const final{ \
        static auto clsInfos = IMetaUtil::getMetaClassInfoMap(staticMetaObject);    \
        return clsInfos;    \
    }   \
    virtual QMetaProperty getMetaProperty(const QString& name) const final {   \
        return IMetaUtil::getMetaPropertyByName(staticMetaObject, name);    \
    }   \
    virtual const QVector<QMetaProperty>& getMetaProperties() const final {    \
        static auto props = IMetaUtil::getMetaProperties(staticMetaObject);  \
        return props;   \
    }   \
    virtual QVariant getFieldValue(const QString& name) const final {   \
        const auto& property = getMetaProperty(name);  \
        return IMetaUtil::readProperty(property, this); \
    }   \
    virtual void setFieldValue(const QString& name, const QVariant& value) final{     \
        const auto& property = getMetaProperty(name);  \
        IMetaUtil::writeProperty(property, this, value);    \
    }   \
    virtual QJsonObject toJson() const final{   \
        return {};  \
    }   \
    virtual const QStringList& getIgnorableFieldNames() const override{ \
        static QStringList ignoredFields = IMetaUtil::getIgnoredFields(staticMetaObject);   \
        return ignoredFields;   \
    }   \
    virtual const QVector<int>& getIgnorableFieldIndexes() const override{  \
        static QVector<int> ignoredFields = IMetaUtil::getIgnoredFieldIndexes(staticMetaObject);   \
        return ignoredFields;   \
    }   \
    virtual bool isIgnorableField(const QString& name) const override{  \
        static const QStringList ignoredFields = getIgnorableFieldNames();  \
        return ignoredFields.contains(name);    \
    }   \
    virtual bool isIgnorableField(int index) const override{    \
        static const QVector<int> ignoredFields = getIgnorableFieldIndexes();   \
        return ignoredFields.contains(index);   \
    }   \
    virtual const QStringList& getMetaFieldNames() const override{  \
        static QStringList fieldNames = IMetaUtil::getMetaPropertyNames(staticMetaObject);  \
        return fieldNames;  \
    }   \
private:


#define $AsBean(klassName) \
public: \
    $_UseGadget(klassName) \
public: \
    operator QString(){ \
        return toString(); \
    } \
    static klassName fromVariantMap(const QMap<QString, QVariant>&map){ \
        klassName bean; \
        IMetaUtil::fromVariantMap(&bean, bean.staticMetaObject, map); \
        return bean; \
    } \
    static klassName fromJson(const QJsonObject& obj){ \
        klassName bean; \
        IMetaUtil::fromJsonObject(&bean, bean.staticMetaObject, obj); \
        return bean; \
    } \
    bool operator==(const klassName& that){ \
        return isEqualTo(&that); \
    } \
    klassName clone(){  \
        return klassName(*this);    \
    }   \
private:

#define $BeanFieldDeclare(type, name) \
    Q_PROPERTY(type name MEMBER name)

//! @note 这里我们使用 空 列表初始化，来保证 基本类型被置为 0.
#define $BeanField_2(type, name) \
    $BeanFieldDeclare(type, name) \
    type name {};

#define $BeanField_3(type, name, value) \
    $BeanFieldDeclare(type, name) \
    type name {value};

#define $BeanField_(N) $BeanField_##N
#define $BeanField_EVAL(N) $BeanField_(N)
#define $BeanField(...) PP_EXPAND( $BeanField_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define PP_BEAN_INGNORED_KEY(name)  \
    PP_STRING(iwebcore_bean_field_ignorable_##name)

#define $FieldIgnorable(name) \
    Q_CLASSINFO(PP_BEAN_INGNORED_KEY(name), #name)
