#include "IMetaUtil.h"
#include "core/base/IConvertUtil.h"

$PackageWebCoreBegin

inline int IMetaUtil::getMetaTypeId(const QString &name)
{
    for(int index=QMetaType::User; ;index++){
        QString typeName = QMetaType::typeName(index);
        if(typeName.isEmpty()){
            break;
        }
        if(typeName == name){
            return index;
        }
    }
    return QMetaType::type(name.toUtf8());
}

inline QString IMetaUtil::getMetaTypeName(int id)
{
    return QMetaType::typeName(id);
}

inline QString IMetaUtil::getMetaClassName(const QMetaObject &meta)
{
    return meta.className();
}

inline QString IMetaUtil::getMetaClassName(const QMetaObject *meta)
{
    return meta->className();
}

inline QMap<QString, QString> IMetaUtil::getMetaClassInfoMap(const QMetaObject& meta)
{
    QMap<QString, QString> ret;
    int count = meta.classInfoCount();
    for(int i=0; i<count; i++){
        auto info = meta.classInfo(i);
        ret[info.name()] = info.value();
    }
    return ret;
}

inline QMap<QString, QString> IMetaUtil::getMetaClassInfoMap(const QMetaObject* meta)
{
    QMap<QString, QString> ret;
    int count = meta->classInfoCount();
    for(int i=0; i<count; i++){
        auto info = meta->classInfo(i);
        ret[info.name()] = info.value();
    }
    return ret;
}

// no recomended,
inline QString IMetaUtil::getMetaClassInfoByName(const QMetaObject &meta, const QString &name, const QString &defaultVal)
{
    auto metaClsInfo = getMetaClassInfoMap(meta);
    return getMetaClassInfoByName(metaClsInfo, name, defaultVal);
}

// no recomended
inline QString IMetaUtil::getMetaClassInfoByName(const QMetaObject *meta, const QString &name, const QString &defaultVal)
{
    auto metaClsInfo = getMetaClassInfoMap(meta);
    return getMetaClassInfoByName(metaClsInfo, name, defaultVal);
}

// recommend
inline QString IMetaUtil::getMetaClassInfoByName(const QMap<QString, QString> &map, const QString &name, const QString &defaultVal)
{
    if(map.contains(name)){
        return map[name];
    }
    return defaultVal;
}

inline QMetaProperty IMetaUtil::getMetaPropertyByName(const QMetaObject& meta, QString name)
{
    return getMetaPropertyByName(&meta, name);
}

inline QMetaProperty IMetaUtil::getMetaPropertyByName(const QMetaObject *meta, QString name)
{
    auto props = getMetaProperties(meta);
    return getMetaPropertyByName(props, name);
}

inline QMetaProperty IMetaUtil::getMetaPropertyByName(const QVector<QMetaProperty> &props, QString name)
{
    auto it = std::find_if(props.begin(), props.end(), [=](const QMetaProperty& prop){
        return prop.name() == name;
    });
    if(it != props.end()){
        return *it;
    }
    return {};
}

inline QStringList IMetaUtil::getIgnoredFields(const QMetaObject &meta)
{
    QStringList ignoredFields;
    static const QString prefix = "iwebcore_bean_field_ignorable_";
    auto clsInfo = IMetaUtil::getMetaClassInfoMap(meta);
    auto keys = clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(prefix)){
            ignoredFields.append(clsInfo[key]);
        }
    }
    return ignoredFields;
}

inline QVector<int> IMetaUtil::getIgnoredFieldIndexes(const QMetaObject &meta)
{
    static const QString prefix = "iwebcore_bean_field_ignorable_";

    QVector<int> ignoredFields;
    auto clsInfo = getMetaClassInfoMap(meta);
    auto props = getMetaProperties(meta);
    auto keys = clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(prefix)){
            QString name = clsInfo[key];
            int i=0;
            for(const auto& prop : props){
                if(name == prop.name()){
                    ignoredFields.append(i);
                    break;
                }
                i++;
            }

        }
    }
    return ignoredFields;
}



//QVector<QMetaMethod> IMetaUtil::getPreRunMetaMethod(const QMetaObject &meta)
//{
//    return getPreRunMetaMethod(&meta);
//}

//QVector<QMetaMethod> IMetaUtil::getPreRunMetaMethod(const QMetaObject *meta)
//{
//    static const char* PRE_RUN_METHOD_PREFIX{"IWebPreRun_"};
//    QVector<QMetaMethod> ret;
//    auto methods = getMetaMethods(meta);
//    for(auto method : methods){
//        if(method.name().startsWith(PRE_RUN_METHOD_PREFIX) && method.parameterCount() == 0
//                && method.returnType() == QMetaType::Void){
//            ret.append(method);
//        }
//    }
//    return ret;
//}

inline QVector<QMetaMethod> IMetaUtil::getMetaMethods(const QMetaObject &meta)
{
    return getMetaMethods(&meta);
}

inline QVector<QMetaMethod> IMetaUtil::getMetaMethods(const QMetaObject *meta)
{
    QVector<QMetaMethod> ret;
    auto count = meta->methodCount();
    for(int i=0; i<count; i++){
        ret.append(meta->method(i));
    }
    return ret;
}

inline QVector<QMetaProperty> IMetaUtil::getMetaProperties(const QMetaObject &meta)
{
    QVector<QMetaProperty> ret;
    auto count = meta.propertyCount();
    for(int i=0; i<count; i++){
        ret.append(meta.property(i));
    }
    return ret;
}

inline QVector<QMetaProperty> IMetaUtil::getMetaProperties(const QMetaObject *meta)
{
    QVector<QMetaProperty> ret;
    auto count = meta->propertyCount();
    for(int i=0; i<count; i++){
        ret.append(meta->property(i));
    }
    return ret;
}

inline QStringList IMetaUtil::getMetaPropertyNames(const QMetaObject &meta)
{
    return getMetaPropertyMap(meta).keys();
}

inline QMap<QString, QMetaProperty> IMetaUtil::getMetaPropertyMap(const QMetaObject &meta)
{
    QMap<QString, QMetaProperty> ret;
    auto count = meta.propertyCount();
    for(int i=0; i<count; i++){
        const auto& property = meta.property(i);
        ret[property.name()] = property;
    }
    return ret;
}

inline QMap<QString, QMetaProperty> IMetaUtil::getMetaPropertyMap(const QMetaObject *meta)
{
    QMap<QString, QMetaProperty> ret;
    auto count = meta->propertyCount();
    for(int i=0; i<count; i++){
        const auto& property = meta->property(i);
        ret[property.name()] = property;
    }
    return ret;
}

inline QMap<QString, QVariant> IMetaUtil::toVariantMap(const void *handler, const QMetaObject &meta)
{
    QMap<QString, QVariant> map;
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        map[prop.name()] = readProperty(prop, handler);
    }
    return map;
}

inline QMap<QString, QVariant> IMetaUtil::toVariantMap(const void *handler, const QMetaObject *meta)
{
    QMap<QString, QVariant> map;
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        map[prop.name()] = readProperty(prop, handler);
    }
    return map;
}

inline void IMetaUtil::fromJsonObject(void *handler, const QMetaObject &meta, const QJsonObject &obj)
{
    auto map = IConvertUtil::toMap(obj);
    return fromVariantMap(handler, meta, map);
}

inline void IMetaUtil::fromJsonObject(void *handler, const QMetaObject *meta, const QJsonObject &obj)
{
    auto map = IConvertUtil::toMap(obj);
    return fromVariantMap(handler, meta, map);
}


inline void IMetaUtil::fromVariantMap(void *handler, const QMetaObject &meta, const QMap<QString, QVariant> &map)
{
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        QString name = prop.name();
        if(map.contains(name)){
            writeProperty(prop, handler, map[name]);
        }
    }
}

inline void IMetaUtil::fromVariantMap(void *handler, const QMetaObject *meta, const QMap<QString, QVariant> &map)
{
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        QString name = prop.name();
        if(map.contains(name)){
            writeProperty(prop, handler, map[name]);
        }
    }
}

inline bool IMetaUtil::writeProperty(const QMetaProperty &prop, void *handler, const QVariant &value)
{
    Q_ASSERT(!QString(prop.name()).isEmpty());
    if(prop.isWritable()){
        prop.writeOnGadget(handler, value);
        return true;
    }
    return false;
}

inline QVariant IMetaUtil::readProperty(const QMetaProperty &prop, const void *handler)
{
    return prop.readOnGadget(handler);
}

$PackageWebCoreEnd
