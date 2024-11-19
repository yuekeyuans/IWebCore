#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IPreProcessorUtil.h"

$PackageWebCoreBegin

class IGadgetUnit
{
public:
    IGadgetUnit() = default;
    virtual ~IGadgetUnit() = default;

    virtual const QStringList& getIgnorableFieldNames() const;
    virtual const QVector<int>& getIgnorableFieldIndexes() const;
    virtual bool isIgnorableField(const QString& name) const;
    virtual bool isIgnorableField(int index) const;

    virtual QVariant getFieldValue(const QString& name) const;
    virtual void setFieldValue(const QString& name, const QVariant& value); // no const

    virtual QJsonValue toJson(bool* ok=nullptr) const = 0;
    virtual bool loadJson(const QJsonValue& value) = 0;

protected:
    QJsonValue toJsonValueOfBeanType(const void* handle, const QMetaProperty& prop, bool* ok) const;
    QJsonValue toJsonValueOfPlainType(int, const QVariant& value, bool* ok) const;

    bool loadJsonValueOfBeanType(const void* handle, const QMetaProperty& prop, const QJsonValue& value);
    bool loadJsonValueOfPlainType(const void* handle, const QMetaProperty& prop, const QJsonValue& value);
};

$PackageWebCoreEnd
