#pragma once

#include "core/util/IPreProcessorUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/bean/IBeanTypeManage.h"

#define $BeanFieldDeclare(type, name)                                                               \
private:                                                                                            \
    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)                                   \
    void $write_##name##_value(const type & value){this-> name = value; }                           \
    Q_INVOKABLE IJson $##name##_toJsonValue() const {                                               \
        return IJsonUtil::toJson( name );                                                           \
    }                                                                                               \
    Q_INVOKABLE bool $##name##_fromJsonValue(const IJson& json) {                                   \
        return IJsonUtil::fromJson(& name, json);                                                   \
    }                                                                                               \
public:

#define $BeanField_2(type, name) \
    type name {};                \
    $BeanFieldDeclare(type, name)

#define $BeanField_3(type, name, value1) \
    $BeanFieldDeclare(type, name) \
    type name {value1};

#define $BeanField_4(type, name, value1, value2) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2};

#define $BeanField_5(type, name, value1, value2, value3) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3};

#define $BeanField_6(type, name, value1, value2, value3, value4) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4};

#define $BeanField_7(type, name, value1, value2, value3, value4, value5) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5};

#define $BeanField_8(type, name, value1, value2, value3, value4, value5, value6) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6};

#define $BeanField_9(type, name, value1, value2, value3, value4, value5, value6, value7) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7};

#define $BeanField_10(type, name, value1, value2, value3, value4, value5, value6, value7, value8) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8};

#define $BeanField_11(type, name, value1, value2, value3, value4, value5, value6, value7, value8, value9) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8, value9};

#define $BeanField_12(type, name, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10) \
    $BeanFieldDeclare(type, name) \
    type name {value1, value2, value3, value4, value5, value6, value7, value8, value9, value10};

#define $BeanField_(N) $BeanField_##N
#define $BeanField_EVAL(N) $BeanField_(N)
#define $BeanField(...) PP_EXPAND( $BeanField_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// container
#define $AsBeanSequentialContainer(ContainerName, Container, Bean)                                                                           \
class Bean ## ContainerName : public IBeanWare, public Container< Bean >, public ITaskInstantUnit< Bean ## ContainerName >                   \
{                                                                                                                                            \
public:                                                                                                                                      \
    virtual IJson toJson() const final{                                                                                                      \
        IJson obj = IJson::array();                                                                                                          \
        for(const auto& bean : *this){                                                                                                       \
            obj.emplace_back(bean.toJson());                                                                                                 \
        }                                                                                                                                    \
        return obj;                                                                                                                          \
    }                                                                                                                                        \
    virtual bool loadJson(const IJson& json) final {                                                                                         \
        if(!json.is_array()) return false;                                                                                                   \
        for(const auto& val : json){                                                                                                         \
            Bean bean;                                                                                                                       \
            if(!bean.loadJson(val)) return false;                                                                                            \
            this->push_back(std::move(bean));                                                                                                \
        }                                                                                                                                    \
        return true;                                                                                                                         \
    }                                                                                                                                        \
                                                                                                                                             \
private:                                                                                                                                     \
    virtual void $task() final{                                                                                                              \
        static std::once_flag flag;                                                                                                          \
        std::call_once(flag, [](){                                                                                                           \
            auto id1 = IMetaUtil::registerMetaType< Bean ## ContainerName >();                                                               \
            IBeanTypeManage::instance()->registerBeanId(id1);                                                                                \
            IBeanTypeManage::instance()->registerFromJson(id1,                                                                             \
                [](void* ptr, const IJson& json)->bool{return static_cast< Bean ## ContainerName *>(ptr)->loadJson(json);}                   \
            );                                                                                                                               \
            auto id2 = IMetaUtil::registerMetaType<Container < Bean >>();                                                                    \
            IBeanTypeManage::instance()->registerBeanId(id2);                                                                                \
            IBeanTypeManage::instance()->registerFromJson(id2,                                                                             \
                [](void* ptr, const IJson& json)->bool{return IJsonUtil::fromJson(static_cast< Container < Bean >*>(ptr), json);}            \
            );                                                                                                                               \
        });                                                                                                                                  \
    }                                                                                                                                        \
};

#define $AsBeanContainer(Bean)  \
    $AsBeanSequentialContainer(QList, QList, Bean) \
    $AsBeanSequentialContainer(QVector, QVector, Bean)   \
    $AsBeanSequentialContainer(StdList, std::list, Bean) \
    $AsBeanSequentialContainer(StdVector, std::vector, Bean)
