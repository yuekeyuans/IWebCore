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

class StudentBeanMapRegistration : public ITaskInstantUnit<StudentBeanMapRegistration>
{
    virtual void $task() final;
};

inline void StudentBeanMapRegistration::$task()
{
    auto id = IMetaUtil::registerMetaType<QMap<QString, StudentBean>>();
    IBeanTypeManage::instance()->registerFromJson(id, [](void* ptr, const IJson&)->bool{
        return false;
    });
}


$AsBeanContainer(StudentBean)
