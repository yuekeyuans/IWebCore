#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IJsonUtil.h"

$PackageWebCoreBegin

template<typename T>
struct IBeanRegisterTypeUnit
{
    static void registType(){
        registBean();

//        registerQList();
//        registerStdList();
//        registerQVector();
//        registerStdVector();

//        registerQStringQMap();
//        registerStdStringQMap();
//        registerIStringQMap();
    }

    static void registBean()
    {
        auto ids = IMetaUtil::registerMetaType<T>();
        for(auto id : ids){
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerFromJson(id,
                [](void* ptr, const IJson& json)->bool{ return static_cast<T*>(ptr)->loadJson(json);}
            );
        }
    }
//    static void registerQList()
//    {
//        auto id = IMetaUtil::registerMetaType<QList<T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<QList<T>*>(ptr), json);}
//        );
//    }
//    static void registerStdList()
//    {
//        auto id = IMetaUtil::registerMetaType<std::list<T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<std::list<T>*>(ptr), json);}
//        );
//    }
//    static void registerQVector()
//    {
//        auto id = IMetaUtil::registerMetaType<QVector<T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<QVector<T>*>(ptr), json);}
//        );
//    }
//    static void registerStdVector()
//    {
//        auto id = IMetaUtil::registerMetaType<std::vector<T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<std::vector<T>*>(ptr), json);}
//        );
//    }
//    static void registerQStringQMap()
//    {
//        auto id = IMetaUtil::registerMetaType<QMap<QString, T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<QMap<QString, T>*>(ptr), json);}
//        );
//    }

//    static void registerStdStringQMap()
//    {
//        auto id = IMetaUtil::registerMetaType<QMap<std::string, T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<QMap<std::string, T>*>(ptr), json);}
//        );
//    }

//    static void registerIStringQMap()
//    {
//        auto name = "QMap<IString, " + IMetaUtil::getBareTypeName<T>() + ">";
//        auto id = IMetaUtil::registerMetaType<QMap<IString, T>>();
//        IBeanTypeManage::instance()->registerFromJson(id,
//            [](void* ptr, const IJson& json)->bool{ return IJsonUtil::fromJson(static_cast<QMap<IString, T>*>(ptr), json);}
//        );
//    }
};

$PackageWebCoreEnd
