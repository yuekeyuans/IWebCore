#pragma once

#include "core/bean/IBeanInterface.h"

using namespace IWebCore;

class StudentBean : public IBeanInterface<StudentBean>
{
    Q_GADGET
public:
    StudentBean();

    $BeanField(int, index, 100)
    $BeanField(QString, name, "yuekeyuan")
};

class StudentBeanQList : public QList<StudentBean>, public IBeanWare,
      public ITaskInstantUnit<StudentBeanQList>
{
public:
    virtual IJson toJson() const final{
        IJson obj = IJson::object();
        for(const auto& bean : *this){
            obj.push_back(bean.toJson());
        }
        return obj;
    }
    virtual bool loadJson(const IJson& json) final
    {
        this->clear();
        if(!json.is_array()){
            return false;
        }
        for(const IJson& val : json){
            StudentBean bean;
            if(bean.loadJson(val)){
                return false;
            }
            this->append(bean);
        }
        return true;
    }

private:
    virtual void $task() final{
        qDebug() << __FUNCTION__ << "22222222222222";
    }
};
