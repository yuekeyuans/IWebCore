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
    QSet<int> registerMetaType(QStringList names={});

    template<typename T>
    std::string getBareTypeName();

    QString demangleName(const char*);
}

template<typename T>
QSet<int> IMetaUtil::registerMetaType(QStringList names)
{
    static QSet<int> s_id;
    static std::once_flag flag;
    std::call_once(flag, [=](){
        auto names_ = names;
        if(names_.isEmpty()){
            QString name = QString::fromStdString(getBareTypeName<T>());

            names_.append(name);
            if(!name.startsWith("std::")){
                if(name.contains("::")){
                    names_.append(name.split("::").last());
                }
            }
        }

        for(auto name : names_){
            s_id << qRegisterMetaType<T>(name.toUtf8());
            s_id << qRegisterMetaType<T>(QString((name + "&")).toUtf8());
        };
        qDebug() << names_ << s_id;
    });
    return s_id;
}

template<typename T>
std::string IMetaUtil::getBareTypeName()
{
    QString name = demangleName(typeid(T).name());
    if(name.startsWith("class ")){
        name = name.mid(6);
    }
    if(name.startsWith("struct ")){
        name = name.mid(7);
    }
    return name.replace("<class ", "<").replace(",class ", ", ").toStdString();
}

$PackageWebCoreEnd
