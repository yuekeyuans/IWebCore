#include "IGadgetUnit.h"

#include "core/base/IConstantUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

const QString& IGadgetUnit::className() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static QString name;
    return name;
}

QMetaObject IGadgetUnit::getMetaObject() const
{
    qFatal(IConstantUtil::InheritedMethod);
    return {};
}

const QVector<QMetaMethod>& IGadgetUnit::getMetaMethods() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static QVector<QMetaMethod> m_vector;
    return m_vector;
}

const QMap<QString, QString>& IGadgetUnit::getMetaClassInfos() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static QMap<QString, QString> m_info;
    return m_info;
}

QMetaProperty IGadgetUnit::getMetaProperty(const QString &name) const
{
    Q_UNUSED(name);
    qFatal(IConstantUtil::InheritedMethod);
    return {};
}

const QVector<QMetaProperty>& IGadgetUnit::getMetaProperties() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static QVector<QMetaProperty> m_props;
    return m_props;
}

const QStringList &IGadgetUnit::getMetaFieldNames() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static QStringList names;
    return names;
}

// 这个是指在 bean 自动装配的过程中, 这一个 field 可以被忽略
const QStringList& IGadgetUnit::getIgnorableFieldNames() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static const QStringList names;
    return names;
}

const QVector<int>& IGadgetUnit::getIgnorableFieldIndexes() const
{
    qFatal(IConstantUtil::InheritedMethod);
    static const QVector<int> indexes;
    return indexes;
}

bool IGadgetUnit::isIgnorableField(const QString &name) const
{
    Q_UNUSED(name)
    qFatal(IConstantUtil::InheritedMethod);
    return {};
}

bool IGadgetUnit::isIgnorableField(int index) const
{
    Q_UNUSED(index)
    qFatal(IConstantUtil::InheritedMethod);
    return {};
}

QVariant IGadgetUnit::getFieldValue(const QString &name) const
{
    Q_UNUSED(name);
    qFatal(IConstantUtil::InheritedMethod);
    return {};
}

void IGadgetUnit::setFieldValue(const QString &name, const QVariant &value)
{
    Q_UNUSED(name);
    Q_UNUSED(value);
    qFatal(IConstantUtil::InheritedMethod);
}

QJsonObject IGadgetUnit::toJson() const
{
    qFatal(IConstantUtil::InheritedMethod);
    return {};
}

QMap<QString, QVariant> IGadgetUnit::toVariantMap() const
{
    return IMetaUtil::toVariantMap(this, getMetaObject());
}

QString IGadgetUnit::toString() const
{
    return IConvertUtil::toString(toJson());
}

void IGadgetUnit::load(const QJsonObject &obj)
{
    IMetaUtil::fromJsonObject(this, getMetaObject(), obj);
}

void IGadgetUnit::load(const QMap<QString, QVariant> &map)
{
    IMetaUtil::fromVariantMap(this, getMetaObject(), map);
}

bool IGadgetUnit::isEqualTo(const IGadgetUnit *gadget)
{
    return isEqualTo(*gadget);
}

bool IGadgetUnit::isEqualTo(const IGadgetUnit &gadget)
{
    if(gadget.className() != this->className()){
        return false;
    }

    auto props = this->getMetaProperties();
    for(const auto& prop : props){
        QString propName = prop.name();
        auto val1 = this->getFieldValue(propName);
        auto val2 = gadget.getFieldValue(propName);
        if(val1.type() == QVariant::Bool){
            bool ok;
            auto thisBool = IConvertUtil::toBool(val1.toBool(), ok);
            auto thatBool = IConvertUtil::toBool(val2.toBool(), ok);
            if(thisBool != thatBool){
                return false;
            }
        }else if(val1 != val2){
            return false;
        }
    }
    return true;
}

$PackageWebCoreEnd
