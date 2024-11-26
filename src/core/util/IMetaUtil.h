#pragma once

#include "core/util/ITraitUtil.h"

$PackageWebCoreBegin

namespace IMetaUtil
{
    const char* getMetaClassName(const QMetaObject& meta);

    QMap<QString, QString> getMetaClassInfoMap(const QMetaObject& meta);  // resolve for Q_GADGET

    QString getMetaClassInfoByName(const QMetaObject& meta, const QString& name, const QString& defaultVal = "");
    QString getMetaClassInfoByName(const QMap<QString, QString>& map, const QString& name, const QString& defaultVal = "");

    std::vector<QMetaProperty> getMetaProperties(const QMetaObject &meta);
    QStringList getMetaPropertyNames(const QMetaObject& meta);

    QMap<QString, QMetaProperty> getMetaPropertyMap(const QMetaObject& meta);

    QMetaProperty getMetaPropertyByName(const QMetaObject& meta, QString name);
    QMetaProperty getMetaPropertyByName(const std::vector<QMetaProperty>& props, QString name);

    QVector<QMetaMethod> getMetaMethods(const QMetaObject& meta);

    bool writeProperty(const QMetaProperty& prop, void* handler,  const QVariant& value);
    QVariant readProperty(const QMetaProperty& prop, const void* handler);

    template<typename T>
    int registerMetaType();

    template<typename T>
    const std::string& getTypename();

    template<typename T>
    const std::string& getBareTypeName();
}

namespace detail
{
    QString demangleName(const char*);
}

template<typename T>
int IMetaUtil::registerMetaType()
{
    QStringList names;
    QString name = QString::fromStdString(getTypename<T>());
    if(name.contains(" ")){
        name = name.split(" ").last();
    }
    names.append(name);
    if(name.contains("::")){
        names.append(name.split("::").last());
    }

    QList<int> ids;
    for(auto name : names){
        ids << qRegisterMetaType<T>(name.toUtf8());
        ids << qRegisterMetaType<T>(QString((name + "&")).toUtf8());
    };
    return ids.first();
}

template<typename T>
const std::string& IMetaUtil::getTypename(){
    static std::string typeName = detail::demangleName(typeid(T).name()).toStdString();
    return typeName;
}

template<typename T>
const std::string& IMetaUtil::getBareTypeName()
{
    QString name = detail::demangleName(typeid(T).name());
    if(name.startsWith("class ")){
        name = name.mid(6);
    }
    static std::string typeName = name.replace("<class ", "<").replace(",class ", ", ").toStdString();
    return typeName;
}

$PackageWebCoreEnd
