#include "IMetaUtil.h"
#include <vector>

$PackageWebCoreBegin

const char* IMetaUtil::getMetaClassName(const QMetaObject &meta)
{
    return meta.className();
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

QString IMetaUtil::getMetaClassInfoByName(const QMetaObject &meta, const QString &name, const QString &defaultVal)
{
    auto metaClsInfo = getMetaClassInfoMap(meta);
    return getMetaClassInfoByName(metaClsInfo, name, defaultVal);
}

QString IMetaUtil::getMetaClassInfoByName(const QMap<QString, QString> &map, const QString &name, const QString &defaultVal)
{
    if(map.contains(name)){
        return map[name];
    }
    return defaultVal;
}

QMetaProperty IMetaUtil::getMetaPropertyByName(const QMetaObject& meta, QString name)
{
    auto props = getMetaProperties(meta);
    return getMetaPropertyByName(props, name);
}

QMetaProperty IMetaUtil::getMetaPropertyByName(const std::vector<QMetaProperty> &props, QString name)
{
    auto it = std::find_if(props.begin(), props.end(), [=](const QMetaProperty& prop){
        return prop.name() == name;
    });
    if(it != props.end()){
        return *it;
    }
    return {};
}

//QStringList IMetaUtil::getIgnoredFields(const QMetaObject &meta)
//{
//    QStringList ignoredFields;
//    static const QString prefix = "iwebcore_bean_field_ignorable_";
//    auto clsInfo = IMetaUtil::getMetaClassInfoMap(meta);
//    auto keys = clsInfo.keys();
//    for(auto key : keys){
//        if(key.startsWith(prefix)){
//            ignoredFields.append(clsInfo[key]);
//        }
//    }
//    return ignoredFields;
//}

//QVector<int> IMetaUtil::getIgnoredFieldIndexes(const QMetaObject &meta)
//{
//    static const QString prefix = "iwebcore_bean_field_ignorable_";

//    QVector<int> ignoredFields;
//    auto clsInfo = getMetaClassInfoMap(meta);
//    auto props = getMetaProperties(meta);
//    auto keys = clsInfo.keys();
//    for(auto key : keys){
//        if(key.startsWith(prefix)){
//            QString name = clsInfo[key];
//            int i=0;
//            for(const auto& prop : props){
//                if(name == prop.name()){
//                    ignoredFields.append(i);
//                    break;
//                }
//                i++;
//            }

//        }
//    }
//    return ignoredFields;
//}

QVector<QMetaMethod> IMetaUtil::getMetaMethods(const QMetaObject &meta)
{
    QVector<QMetaMethod> ret;
    auto count = meta.methodCount();
    for(int i=0; i<count; i++){
        ret.append(meta.method(i));
    }
    return ret;
}


std::vector<QMetaProperty> IMetaUtil::getMetaProperties(const QMetaObject &meta)
{
    std::vector<QMetaProperty> ret;
    auto count = meta.propertyCount();
    for(int i=0; i<count; i++){
        ret.push_back(meta.property(i));
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

QString IMetaUtil::demangleName(const char *name)
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
