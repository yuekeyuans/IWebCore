﻿#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/ITraitHelper.h"

$PackageWebCoreBegin


namespace IMetaUtilHelper {
    static QString demangleName(const char*);
}

namespace IMetaUtil
{
    int getMetaTypeId(const QString& name);
    QString getMetaTypeName(int id);

    QString getMetaClassName(const QMetaObject& meta);
    QString getMetaClassName(const QMetaObject* meta);

    QMap<QString, QString> getMetaClassInfoMap(const QMetaObject& meta);  // resolve for Q_GADGET
    QMap<QString, QString> getMetaClassInfoMap(const QMetaObject* meta);  // resolve for Q_OBJECT

    QString getMetaClassInfoByName(const QMetaObject& meta, const QString& name, const QString& defaultVal = "");
    QString getMetaClassInfoByName(const QMetaObject* meta, const QString& name, const QString& defaultVal = "");
    QString getMetaClassInfoByName(const QMap<QString, QString>& map, const QString& name, const QString& defaultVal = "");

    QVector<QMetaProperty> getMetaProperties(const QMetaObject &meta);
    QVector<QMetaProperty> getMetaProperties(const QMetaObject *meta);

    QStringList getMetaPropertyNames(const QMetaObject& meta);
//    QStringList getMetaPropertyNames(const QMetaObject* meta);

    QMap<QString, QMetaProperty> getMetaPropertyMap(const QMetaObject& meta);
    QMap<QString, QMetaProperty> getMetaPropertyMap(const QMetaObject* meta);

    QMetaProperty getMetaPropertyByName(const QMetaObject& meta, QString name);
    QMetaProperty getMetaPropertyByName(const QMetaObject* meta, QString name);
    QMetaProperty getMetaPropertyByName(const QVector<QMetaProperty>& props, QString name);

    QStringList getIgnoredFields(const QMetaObject& meta);
    QVector<int> getIgnoredFieldIndexes(const QMetaObject& meta);

    QVector<QMetaMethod> getMetaMethods(const QMetaObject& meta);
    QVector<QMetaMethod> getMetaMethods(const QMetaObject* meta);

    QMap<QString, QVariant> toVariantMap(const void* handler, const QMetaObject& meta);
    QMap<QString, QVariant> toVariantMap(const void* handler, const QMetaObject* meta);

    void fromJsonObject(void* handler, const QMetaObject&meta, const QJsonObject& obj);
    void fromJsonObject(void* handler, const QMetaObject*meta, const QJsonObject& obj);

    void fromVariantMap(void* handler, const QMetaObject&meta, const QMap<QString, QVariant>& map);
    void fromVariantMap(void* handler, const QMetaObject*meta, const QMap<QString, QVariant>& map);

    bool writeProperty(const QMetaProperty& prop, void* handler,  const QVariant& value);
    QVariant readProperty(const QMetaProperty& prop, const void* handler);

    template<typename T>
    void registerMetaType();

    template<typename T>
    void registerBaseType(const QString& name);

    template<typename T>
    QString getTypename();
}

template<typename T>
void IMetaUtil::registerMetaType()
{
    QStringList names;
    QString name = getTypename<T>();
    if(name.contains(" ")){
        name = name.split(" ").last();
    }
    names.append(name);
    if(name.contains("::")){
        names.append(name.split("::").last());
    }

    for(auto name : names){
        qRegisterMetaType<T>(name.toUtf8());
        qRegisterMetaType<T>(QString((name + "&")).toUtf8());
    }
}

template<typename T>
void IMetaUtil::registerBaseType(const QString &name)
{
    qRegisterMetaType<T>(name.toUtf8());
    qRegisterMetaType<T>(QString((name + "&")).toUtf8());
}

template<typename T>
QString IMetaUtil::getTypename(){
    if constexpr (ITraitHelper::is_gadget_v<T>){
        return getMetaClassName(T::staticMetaObject);
    }else{
        return IMetaUtilHelper::demangleName(typeid(T).name());
    }
}

$PackageWebCoreEnd

#include "IMetaUtil.cpp"
