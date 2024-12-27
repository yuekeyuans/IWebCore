#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/bean/IBeanTypeManage.h"

$PackageWebCoreBegin

template<typename T>
struct IBeanRegisterTypeUnit
{
    static void registType();

private:
    // bean
    static void registBean();
    // list vector
    static void registerQList();
    static void registerStdList();
    static void registerQVector();
    static void registerStdVector();

    // QMap
    static void registerQStringQMap();
    static void registerStdStringQMap();
    static void registerIStringQMap();
    static void registerQStringStdMap();
    static void registerStdStringStdMap();
    static void registerIStringStdMap();
};

template<typename T>
void IBeanRegisterTypeUnit<T>::registType()
{
    registBean();

    registerQList();
    registerStdList();
    registerQVector();
    registerStdVector();

    registerQStringQMap();
    registerStdStringQMap();
    registerIStringQMap();

    registerQStringStdMap();
    registerStdStringStdMap();
    registerIStringStdMap();
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registBean()
{
    auto ids = IMetaUtil::registerMetaType<T>();
    for(auto id : ids){
        IBeanTypeManage::instance()->registerBeanId(id);
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<T*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<T*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerQList()
{
    auto ids = IMetaUtil::registerMetaType<QList<T>>();
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<QList<T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<QList<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerStdList()
{
    auto ids = IMetaUtil::registerMetaType<std::list<T>>({"std::list<" + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">"});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<std::list<T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<std::list<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerQVector()
{
    auto ids = IMetaUtil::registerMetaType<QVector<T>>();
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<QVector<T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<QVector<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerStdVector()
{
    auto name = "std::vector<" + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">";
    auto ids = IMetaUtil::registerMetaType<std::vector<T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<std::vector<T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<std::vector<T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerQStringQMap()
{
    auto ids = IMetaUtil::registerMetaType<QMap<QString, T>>();
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<QMap<QString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<QMap<QString, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerStdStringQMap()
{
    auto name = "QMap<std::string, " + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">";
    auto ids = IMetaUtil::registerMetaType<QMap<std::string, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<QMap<std::string, T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<QMap<std::string, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerIStringQMap()
{
    auto name = "QMap<IString, " + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">";
    auto ids = IMetaUtil::registerMetaType<QMap<IString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<QMap<IString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<QMap<IString, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerQStringStdMap()
{
    auto name = "std::map<QString, " + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">";
    auto ids = IMetaUtil::registerMetaType<std::map<QString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<std::map<QString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<std::map<QString, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerStdStringStdMap()
{
    auto name = "std::map<std::string, " + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">";
    auto ids = IMetaUtil::registerMetaType<std::map<std::string, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<std::map<std::string, T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<std::map<std::string, T>*>(ptr));
        });
    }
}

template<typename T>
void IBeanRegisterTypeUnit<T>::registerIStringStdMap()
{
    auto name = "std::map<IString, " + QString::fromStdString(IMetaUtil::getBareTypeName<T>()) + ">";
    auto ids = IMetaUtil::registerMetaType<std::map<IString, T>>({name});
    for(auto id : ids){
        IBeanTypeManage::instance()->registerFromJson(id,[](void* ptr, const IJson& json)->bool{
            return IJsonUtil::fromJson(static_cast<std::map<IString, T>*>(ptr), json);
        });
        IBeanTypeManage::instance()->registerToJson(id, [](void* ptr)->IJson{
            return IJsonUtil::toJson(static_cast<std::map<IString, T>*>(ptr));
        });
    }
}

$PackageWebCoreEnd
