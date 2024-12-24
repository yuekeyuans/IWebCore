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
        IJson obj = IJson::array();
        int len = this->length();
        qDebug() << len;
        for(int i=0; i<len; i++){
            const auto& bean = this->at(i);
            auto value = bean.toJson();
            std::cout << value;
            std::cout << bean.toJson().dump();
            obj.emplace_back(bean.toJson());
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
        static std::once_flag flag;
        std::call_once(flag, [](){
            auto id = IMetaUtil::registerMetaType<StudentBeanQList>();
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerBeanAssign(id,
                [](void* ptr, const IJson& json)->bool{
                    return static_cast<StudentBeanQList*>(ptr)->loadJson(json);
            });
        });

    }
};
