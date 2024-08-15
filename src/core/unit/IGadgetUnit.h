#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IPreProcessorUtil.h"

$PackageWebCoreBegin

class IGadgetUnit
{
public:
    IGadgetUnit() = default;
    virtual ~IGadgetUnit() = default;

    virtual const QString& className() const = 0;
    virtual QMetaObject getMetaObject() const = 0;
    virtual int getMetaTypeId() const = 0;
    virtual const QVector<QMetaMethod>& getMetaMethods() const = 0;
    virtual QMetaMethod getMetaMethod(const QString& name) const = 0;
    virtual const QMap<QString, QString>& getMetaClassInfos() const = 0;
    virtual QMetaProperty getMetaProperty(const QString& name) const = 0;
    virtual const QVector<QMetaProperty>& getMetaProperties() const = 0;
    virtual const QStringList& getMetaFieldNames() const = 0;

    virtual const QStringList& getIgnorableFieldNames() const;
    virtual const QVector<int>& getIgnorableFieldIndexes() const;
    virtual bool isIgnorableField(const QString& name) const;
    virtual bool isIgnorableField(int index) const;

    virtual QVariant getFieldValue(const QString& name) const;
    virtual void setFieldValue(const QString& name, const QVariant& value); // no const

    virtual bool isEqualTo(const IGadgetUnit* gadget) const;
    virtual bool isEqualTo(const IGadgetUnit& gadget) const;

    virtual QJsonValue toJson(bool* ok=nullptr) const final;

    virtual bool loadJson(const QJsonValue& value){
        return true;
    }

private:
    QJsonValue toJsonValueOfBeanType(const void* handle, int type) const;
    QJsonValue toJsonValueOfPlainType(int, const QVariant& value, bool* ok) const;
};

$PackageWebCoreEnd
