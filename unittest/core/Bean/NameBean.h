#pragma once

#include "core/bean/IBeanInterface.h"

class NameBean : public IBeanInterface<NameBean>
{
    Q_GADGET
public:
    NameBean() = default;
    $BeanField(QString, name, "hello world")
};

//$AsBeanList(NameBean)


class NameBeanList : public QList< NameBean >, public IBeanInterface<NameBeanList >
{
    Q_GADGET
public:
    virtual IJson toJson(bool *ok) const final {
        IJson json = IJson::array();
        for(const NameBean & bean : *this){
            json.push_back(bean.toJson(ok));
            if(ok != nullptr && *ok ==false){
                return json;
            }
        }
        return json;
    }
    virtual bool loadJson(const IJson &value) final{
        if(value.is_null()){ return true; }
        if(!value.is_array()){ return false; }
        for(const IJson& value : value){
            NameBean bean;
            if(!bean.loadJson(value)){
                return false;
            }
            this->append(bean);
        }
        return true;
    }
};
