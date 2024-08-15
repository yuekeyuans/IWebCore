#include "IGadgetUnit.h"

#include "core/abort/IGlobalAbort.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/util/IConstantUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/util/IMetaUtil.h"

$PackageWebCoreBegin

const QString& IGadgetUnit::className() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static QString name;
    return name;
}

QMetaObject IGadgetUnit::getMetaObject() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

const QVector<QMetaMethod>& IGadgetUnit::getMetaMethods() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static QVector<QMetaMethod> m_vector;
    return m_vector;
}

QMetaMethod IGadgetUnit::getMetaMethod(const QString &name) const
{
    const auto& methods = getMetaMethods();
    for(const QMetaMethod& method : methods){
        if(method.name() == name){
            return method;
        }
    }
    return {};
}

const QMap<QString, QString>& IGadgetUnit::getMetaClassInfos() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static QMap<QString, QString> m_info;
    return m_info;
}

QMetaProperty IGadgetUnit::getMetaProperty(const QString &name) const
{
    Q_UNUSED(name);
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

const QVector<QMetaProperty>& IGadgetUnit::getMetaProperties() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static QVector<QMetaProperty> m_props;
    return m_props;
}

const QStringList &IGadgetUnit::getMetaFieldNames() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static QStringList names;
    return names;
}

// 这个是指在 bean 自动装配的过程中, 这一个 field 可以被忽略
const QStringList& IGadgetUnit::getIgnorableFieldNames() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static const QStringList names;
    return names;
}

const QVector<int>& IGadgetUnit::getIgnorableFieldIndexes() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static const QVector<int> indexes;
    return indexes;
}

bool IGadgetUnit::isIgnorableField(const QString &name) const
{
    Q_UNUSED(name)
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

bool IGadgetUnit::isIgnorableField(int index) const
{
    Q_UNUSED(index)
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

QVariant IGadgetUnit::getFieldValue(const QString &name) const
{
    Q_UNUSED(name);
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

void IGadgetUnit::setFieldValue(const QString &name, const QVariant &value)
{
    Q_UNUSED(name);
    Q_UNUSED(value);
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
}

bool IGadgetUnit::isEqualTo(const IGadgetUnit *gadget) const
{
    return isEqualTo(*gadget);
}

bool IGadgetUnit::isEqualTo(const IGadgetUnit &gadget) const
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

QJsonValue IGadgetUnit::toJson(bool *ok) const{
    QJsonObject obj;
    const auto& fields = getMetaProperties();
    //        bool ok;
    for(const QMetaProperty& field : fields){
        //            ok = true;
        auto type = field.type();
        if(type >= QMetaType::User){
            obj[field.name()] = toJsonValueOfBeanType(this, type);
        }else{
            auto value = field.readOnGadget(this);
            obj[field.name()] = toJsonValueOfPlainType(type, value, ok);
        }

    }
    return obj;
}

QJsonValue IGadgetUnit::toJsonValueOfBeanType(const void *handle, int type) const
{
    //            auto fun = IBeanTypeManage::instance()->getToJsonFun(getMetaTypeId());
    //            auto ptr = getMetaMethod("$get_" + field.name() + "_ptr");
    //            fun(this, value);
    return {};
}

QJsonValue IGadgetUnit::toJsonValueOfPlainType(int type, const QVariant &value, bool* ok) const
{
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
        return  value.toString();
        break;
    case QMetaType::QStringList:{
        QJsonArray array;
        auto strlist = value.toStringList();
        for(const auto& str : strlist){
            array.append(str);
        }
        return  array;
    }
        break;
    case QMetaType::QByteArray:
        return  QString(value.toByteArray());
        break;
    case QMetaType::QJsonArray:
        return  value.toJsonArray();
        break;
    case QMetaType::QJsonObject:
        return  value.toJsonObject();
        break;
    case QMetaType::QJsonValue:
        return  value.toJsonValue();
        break;
    default:
        ok = false;
        break;
    }
}


$PackageWebCoreEnd
