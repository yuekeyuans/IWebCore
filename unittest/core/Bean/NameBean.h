#pragma once

#include "core/bean/IBeanInterface.h"

class NameBean : public IBeanInterface<NameBean>
{
    Q_GADGET
    $AsBean(NameBean)
public:
    virtual QJsonValue toJson() final{
        QJsonObject obj;
        const auto& fields = getMetaProperties();
        bool ok;
        for(const QMetaProperty& field : fields){
            ok = true;
            auto type = field.type();
            auto value = field.readOnGadget(this);
            if(type > QMetaType::User){
                ok = value.canConvert(QMetaType::QJsonValue);
                if(ok){
                    obj[field.name()] = value.toJsonValue();
                }
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
                    obj[field.name()] = value.toLongLong(&ok);
                    break;
                case QMetaType::ULong:
                case QMetaType::ULongLong:
                    // TODO: 这里需要验证
                    obj[field.name()] = value.toLongLong(&ok);
                    break;
                case QMetaType::Float:
                    obj[field.name()] = value.toFloat(&ok);
                    break;
                case QMetaType::Double:
                    obj[field.name()] = value.toDouble(&ok);
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
public:
    NameBean();
    $BeanField(QString, name, "hello world")
};

