#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"

$PackageWebCoreBegin

class IGadgetUnit
{
public:
    IGadgetUnit() = default;
    virtual ~IGadgetUnit() = default;

    virtual const QString& className() const;
    virtual QMetaObject getMetaObject() const;
    virtual const QVector<QMetaMethod>& getMetaMethods() const;
    virtual const QMap<QString, QString>& getMetaClassInfos() const;
    virtual QMetaProperty getMetaProperty(const QString& name) const;
    virtual const QVector<QMetaProperty>& getMetaProperties() const;

    virtual const QStringList& getMetaFieldNames() const;

    virtual const QStringList& getIgnorableFieldNames() const;
    virtual const QVector<int>& getIgnorableFieldIndexes() const;
    virtual bool isIgnorableField(const QString& name) const;
    virtual bool isIgnorableField(int index) const;

    virtual QVariant getFieldValue(const QString& name) const;
    virtual void setFieldValue(const QString& name, const QVariant& value); // no const

    virtual QJsonObject toJson() const;
    virtual QMap<QString, QVariant> toVariantMap() const;
    virtual QString toString() const;

    virtual void load(const QJsonObject& obj);
    virtual void load(const QMap<QString, QVariant>& variantMap);

    virtual bool isEqualTo(const IGadgetUnit* gadget);
    virtual bool isEqualTo(const IGadgetUnit& gadget);
};

$PackageWebCoreEnd
