#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IPreProcessorUtil.h"

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

    virtual bool isEqualTo(const IGadgetUnit* gadget) const;
    virtual bool isEqualTo(const IGadgetUnit& gadget) const;

    virtual QJsonValue toJson(bool* ok = nullptr) const final{
        QJsonObject obj;
        const auto& fields = getMetaProperties();
//        bool ok;
        for(const QMetaProperty& field : fields){
//            ok = true;
            auto type = field.type();
            auto value = field.readOnGadget(this);
            if(type >= QMetaType::User){
//                ok = value.canConvert(QMetaType::QJsonValue);
//                if(ok){
//                    obj[field.name()] = value.toJsonValue();
//                }
            }else{
                switch (type) {
                case QMetaType::Bool:
                    obj[field.name()] = value.toBool();
                    break;
                case QMetaType::UChar:
                case QMetaType::Char:
                case QMetaType::SChar:
                case QMetaType::Short:
                case QMetaType::UShort:
                case QMetaType::UInt:
                case QMetaType::Int:
                case QMetaType::Long:
                    obj[field.name()] = value.toLongLong(ok);
                    break;
                case QMetaType::ULong:
                case QMetaType::ULongLong:
                    // TODO: 这里需要验证
                    obj[field.name()] = value.toLongLong(ok);
                    break;
                case QMetaType::Float:
                    obj[field.name()] = value.toFloat(ok);
                    break;
                case QMetaType::Double:
                    obj[field.name()] = value.toDouble(ok);
                    break;
                case QMetaType::QString:
                    obj[field.name()] = value.toString();
                    break;
                case QMetaType::QByteArray:
                    obj[field.name()] = QString(value.toByteArray());
                    break;
                case QMetaType::QJsonArray:
                    obj[field.name()] = value.toJsonArray();
                    break;
                case QMetaType::QJsonObject:
                    obj[field.name()] = value.toJsonObject();
                    break;
                case QMetaType::QJsonValue:
                    obj[field.name()] = value.toJsonValue();
                    break;
                default:
                    ok = false;
                    break;
                }
            }
        }
        return obj;
    }

    virtual bool loadJson(const QJsonValue& value){
        return true;
    }
};

$PackageWebCoreEnd
