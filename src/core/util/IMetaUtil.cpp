#include "IMetaUtil.h"
#include "core/util/IConvertUtil.h"

$PackageWebCoreBegin

int IMetaUtil::getMetaTypeId(const QString &name)
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

QString IMetaUtil::getMetaTypeName(int id)
{
    return QMetaType::typeName(id);
}

QString IMetaUtil::getMetaClassName(const QMetaObject &meta)
{
    return meta.className();
}

QString IMetaUtil::getMetaClassName(const QMetaObject *meta)
{
    return meta->className();
}

QMap<QString, QString> IMetaUtil::getMetaClassInfoMap(const QMetaObject& meta)
{
    QMap<QString, QString> ret;
    int count = meta.classInfoCount();
    for(int i=0; i<count; i++){
        auto info = meta.classInfo(i);
        ret[info.name()] = info.value();
    }
    return ret;
}

QMap<QString, QString> IMetaUtil::getMetaClassInfoMap(const QMetaObject* meta)
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
QString IMetaUtil::getMetaClassInfoByName(const QMetaObject &meta, const QString &name, const QString &defaultVal)
{
    auto metaClsInfo = getMetaClassInfoMap(meta);
    return getMetaClassInfoByName(metaClsInfo, name, defaultVal);
}

// no recomended
QString IMetaUtil::getMetaClassInfoByName(const QMetaObject *meta, const QString &name, const QString &defaultVal)
{
    auto metaClsInfo = getMetaClassInfoMap(meta);
    return getMetaClassInfoByName(metaClsInfo, name, defaultVal);
}

// recommend
QString IMetaUtil::getMetaClassInfoByName(const QMap<QString, QString> &map, const QString &name, const QString &defaultVal)
{
    if(map.contains(name)){
        return map[name];
    }
    return defaultVal;
}

QMetaProperty IMetaUtil::getMetaPropertyByName(const QMetaObject& meta, QString name)
{
    return getMetaPropertyByName(&meta, name);
}

QMetaProperty IMetaUtil::getMetaPropertyByName(const QMetaObject *meta, QString name)
{
    auto props = getMetaProperties(meta);
    return getMetaPropertyByName(props, name);
}

QMetaProperty IMetaUtil::getMetaPropertyByName(const QVector<QMetaProperty> &props, QString name)
{
    auto it = std::find_if(props.begin(), props.end(), [=](const QMetaProperty& prop){
        return prop.name() == name;
    });
    if(it != props.end()){
        return *it;
    }
    return {};
}

QStringList IMetaUtil::getIgnoredFields(const QMetaObject &meta)
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

QVector<int> IMetaUtil::getIgnoredFieldIndexes(const QMetaObject &meta)
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

QVector<QMetaMethod> IMetaUtil::getMetaMethods(const QMetaObject &meta)
{
    return getMetaMethods(&meta);
}

QVector<QMetaMethod> IMetaUtil::getMetaMethods(const QMetaObject *meta)
{
    QVector<QMetaMethod> ret;
    auto count = meta->methodCount();
    for(int i=0; i<count; i++){
        ret.append(meta->method(i));
    }
    return ret;
}

QVector<QMetaProperty> IMetaUtil::getMetaProperties(const QMetaObject &meta)
{
    QVector<QMetaProperty> ret;
    auto count = meta.propertyCount();
    for(int i=0; i<count; i++){
        ret.append(meta.property(i));
    }
    return ret;
}

QVector<QMetaProperty> IMetaUtil::getMetaProperties(const QMetaObject *meta)
{
    QVector<QMetaProperty> ret;
    auto count = meta->propertyCount();
    for(int i=0; i<count; i++){
        ret.append(meta->property(i));
    }
    return ret;
}

QStringList IMetaUtil::getMetaPropertyNames(const QMetaObject &meta)
{
    return getMetaPropertyMap(meta).keys();
}

QMap<QString, QMetaProperty> IMetaUtil::getMetaPropertyMap(const QMetaObject &meta)
{
    QMap<QString, QMetaProperty> ret;
    auto count = meta.propertyCount();
    for(int i=0; i<count; i++){
        const auto& property = meta.property(i);
        ret[property.name()] = property;
    }
    return ret;
}

QMap<QString, QMetaProperty> IMetaUtil::getMetaPropertyMap(const QMetaObject *meta)
{
    QMap<QString, QMetaProperty> ret;
    auto count = meta->propertyCount();
    for(int i=0; i<count; i++){
        const auto& property = meta->property(i);
        ret[property.name()] = property;
    }
    return ret;
}

QMap<QString, QVariant> IMetaUtil::toVariantMap(const void *handler, const QMetaObject &meta)
{
    QMap<QString, QVariant> map;
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        map[prop.name()] = readProperty(prop, handler);
    }
    return map;
}

QMap<QString, QVariant> IMetaUtil::toVariantMap(const void *handler, const QMetaObject *meta)
{
    QMap<QString, QVariant> map;
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        map[prop.name()] = readProperty(prop, handler);
    }
    return map;
}

// TODO: 感觉 神智不清这个之后开一线
void IMetaUtil::fromJsonObject(void *handler, const QMetaObject &meta, const QJsonObject &obj)
{
    bool ok;
    auto map = IConvertUtil::toMap(obj, ok);
    return fromVariantMap(handler, meta, map);
}

// TODO：
void IMetaUtil::fromJsonObject(void *handler, const QMetaObject *meta, const QJsonObject &obj)
{
    bool ok;
    auto map = IConvertUtil::toMap(obj, ok);
    return fromVariantMap(handler, meta, map);
}


void IMetaUtil::fromVariantMap(void *handler, const QMetaObject &meta, const QMap<QString, QVariant> &map)
{
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        QString name = prop.name();
        if(map.contains(name)){
            writeProperty(prop, handler, map[name]);
        }
    }
}

void IMetaUtil::fromVariantMap(void *handler, const QMetaObject *meta, const QMap<QString, QVariant> &map)
{
    auto props = getMetaProperties(meta);
    for(const auto& prop : props){
        QString name = prop.name();
        if(map.contains(name)){
            writeProperty(prop, handler, map[name]);
        }
    }
}

bool IMetaUtil::writeProperty(const QMetaProperty &prop, void *handler, const QVariant &value)
{
    Q_ASSERT(!QString(prop.name()).isEmpty());
    if(prop.isWritable()){
        prop.writeOnGadget(handler, value);
        return true;
    }
    return false;
}

QVariant IMetaUtil::readProperty(const QMetaProperty &prop, const void *handler)
{
    return prop.readOnGadget(handler);
}

#if defined(__GNUC__)
    # include <cxxabi.h>
#elif defined(__clang__)

#elif defined(_MSC_VER)
    #include <windows.h>
    #include <dbghelp.h>
    #pragma comment ( lib,"DbgHelp.lib" )
#endif

QString IMetaUtilHelper::demangleName(const char *name)
{
#ifdef __GNUC__
    int status;
     char* demangledName = abi::__cxa_demangle(name, nullptr, nullptr, &status);
     if(status == 0){
         return demangledName;
     }else{
         return name;
     }
#elif defined(__clang__)
    qDebug() << "this should be test when clang applied";
    return name;
#elif defined(_MSC_VER)
    char* demangledName = nullptr;
    HRESULT result = UnDecorateSymbolName(name, demangledName, 0, UNDNAME_COMPLETE);
    if (result == S_OK && demangledName != nullptr) {
        std::string temp(demangledName);
        free(demangledName);
        return QString::fromStdString(temp);
    } else {
        return name;
    }
#else
    return name;
#endif
}
$PackageWebCoreEnd
