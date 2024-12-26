#pragma once

#include "core/bean/IBeanInterface.h"
#include "core/util/IJsonUtil.h"

using namespace IWebCore;

class StudentBean : public IBeanInterface<StudentBean>
{
    Q_GADGET
public:
    StudentBean();

    $BeanField(int, index, 100)
    $BeanField(QString, name, "yuekeyuan")
};


#define $AsBeanSequentialContainer(ContainerName, Container, Bean)                                                                                       \
class Bean ## ContainerName : public IBeanWare, public Container< Bean >, public ITaskInstantUnit< Bean ## ContainerName >                        \
{                                                                                                                                         \
public:                                                                                                                                   \
    virtual IJson toJson() const final{                                                                                                   \
        IJson obj = IJson::array();                                                                                                       \
        for(const auto& bean : *this){                                                                                                    \
            obj.emplace_back(bean.toJson());                                                                                              \
        }                                                                                                                                 \
        return obj;                                                                                                                       \
    }                                                                                                                                     \
    virtual bool loadJson(const IJson& json) final {                                                                                      \
        if(!json.is_array()) return false;                                                                                                \
        for(const auto& val : json){                                                                                                      \
            Bean bean;                                                                                                                    \
            if(!bean.loadJson(val)) return false;                                                                                         \
            this->push_back(std::move(bean));                                                                                                           \
        }                                                                                                                                 \
        return true;                                                                                                                      \
    }                                                                                                                                     \
                                                                                                                                          \
private:                                                                                                                                  \
    virtual void $task() final{                                                                                                           \
        static std::once_flag flag;                                                                                                       \
        std::call_once(flag, [](){                                                                                                        \
            auto id1 = IMetaUtil::registerMetaType< Bean ## ContainerName >();                                                                \
            IBeanTypeManage::instance()->registerBeanId(id1);                                                                             \
            IBeanTypeManage::instance()->registerBeanAssign(id1,                                                                          \
                [](void* ptr, const IJson& json)->bool{return static_cast< Bean ## ContainerName *>(ptr)->loadJson(json);}                    \
            );                                                                                                                            \
            auto id2 = IMetaUtil::registerMetaType<Container < Bean >>();                                                                 \
            IBeanTypeManage::instance()->registerBeanId(id2);                                                                              \
            IBeanTypeManage::instance()->registerBeanAssign(id2,                                                                           \
                [](void* ptr, const IJson& json)->bool{return IJsonUtil::fromJson(static_cast< Container < Bean >*>(ptr), json);}         \
            );                                                                                                                            \
        });                                                                                                                               \
    }                                                                                                                                     \
};

#define $AsBeanContainer(Bean)  \
    $AsBeanSequentialContainer(QList, QList, Bean) \
    $AsBeanSequentialContainer(QVector, QVector, Bean)   \
    $AsBeanSequentialContainer(StdList, std::list, Bean) \
    $AsBeanSequentialContainer(StdVector, std::vector, Bean)

$AsBeanContainer(StudentBean)
