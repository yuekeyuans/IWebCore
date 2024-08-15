#pragma once

#include "core/util/IPreProcessorUtil.h"

#define $_UseGadget()   \
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
    $_UseGadget() \
public: \
    static klassName fromJson(const QJsonObject& obj){ \
        klassName bean; \
        IMetaUtil::fromJsonObject(&bean, bean.staticMetaObject, obj); \
        return bean; \
    } \
    virtual bool operator==(const klassName& value) const {  \
        return isEqualTo(value);    \
    }   \
    virtual bool operator!=(const klassName& value) const {  \
        return !operator==(value);  \
    }   \
    klassName clone(){  \
        return *this;   \
    }   \
private:

#define $BeanFieldDeclare(type, name) \
    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)   \
    Q_INVOKABLE void* $get_ ## name ## _ptr(){ return & name; }     \
    void $write_##name##_value(const type & value){this-> name = value; }

#define $BeanField_2(type, name) \
    $BeanFieldDeclare(type, name) \
    type name {};

#define $BeanField_3(type, name, value) \
    $BeanFieldDeclare(type, name) \
    type name {value};

#define $BeanField_3(type, name, value) \
    $BeanFieldDeclare(type, name) \
    type name {value};

#define $BeanField_3(type, name, value1) \
    $BeanFieldDeclare(type, name) \
    type name {value1};

#define $BeanField_4(type, name, value1, value2) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2};

#define $BeanField_5(type, name, value1, value2, value3) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3};

#define $BeanField_6(type, name, value1, value2, value3, value4) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4};

#define $BeanField_7(type, name, value1, value2, value3, value4, value5) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5};

#define $BeanField_8(type, name, value1, value2, value3, value4, value5, value6) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6};

#define $BeanField_9(type, name, value1, value2, value3, value4, value5, value6, value7) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7};

#define $BeanField_10(type, name, value1, value2, value3, value4, value5, value6, value7, value8) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8};

#define $BeanField_11(type, name, value1, value2, value3, value4, value5, value6, value7, value8, value9) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8, value9};

#define $BeanField_12(type, name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8, value9, value10};

#define $BeanField_(N) $BeanField_##N
#define $BeanField_EVAL(N) $BeanField_(N)
#define $BeanField(...) PP_EXPAND( $BeanField_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_BEAN_INGNORED_KEY(name)  \
    PP_STRING(iwebcore_bean_field_ignorable_##name)

#define $FieldIgnorable(name) \
    Q_CLASSINFO(PP_BEAN_INGNORED_KEY(name), #name)
