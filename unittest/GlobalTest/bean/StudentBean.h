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


class StudentBeanStdList : public IBeanWare, public QVector<StudentBean>, public ITaskInstantUnit<StudentBeanStdList>
{
public:
    virtual IJson toJson() const final{
        IJson obj = IJson::array();
        int len = this->length();
        for(int i=0; i<len; i++){
            const auto& bean = this->at(i);
            auto value = bean.toJson();
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
        for(const auto& val : json){
            StudentBean bean;
            if(!bean.loadJson(val)){
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
            auto id = IMetaUtil::registerMetaType<StudentBeanStdList>();
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerBeanAssign(id,
                [](void* ptr, const IJson& json)->bool{
                    return static_cast<StudentBeanStdList*>(ptr)->loadJson(json);
            });
        });

    }
};


class StudentBeanStdVector : public IBeanWare, public QVector<StudentBean>, public ITaskInstantUnit<StudentBeanStdVector>
{
public:
    virtual IJson toJson() const final{
        IJson obj = IJson::array();
        int len = this->length();
        for(int i=0; i<len; i++){
            const auto& bean = this->at(i);
            auto value = bean.toJson();
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
        for(const auto& val : json){
            StudentBean bean;
            if(!bean.loadJson(val)){
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
            auto id = IMetaUtil::registerMetaType<StudentBeanStdVector>();
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerBeanAssign(id,
                [](void* ptr, const IJson& json)->bool{
                    return static_cast<StudentBeanStdVector*>(ptr)->loadJson(json);
            });
        });

    }
};


class StudentBeanQVector : public IBeanWare, public QVector<StudentBean>, public ITaskInstantUnit<StudentBeanQVector>
{
public:
    virtual IJson toJson() const final{
        IJson obj = IJson::array();
        int len = this->length();
        for(int i=0; i<len; i++){
            const auto& bean = this->at(i);
            auto value = bean.toJson();
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
        for(const auto& val : json){
            StudentBean bean;
            if(!bean.loadJson(val)){
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
            auto id = IMetaUtil::registerMetaType<StudentBeanQVector>();
            IBeanTypeManage::instance()->registerBeanId(id);
            IBeanTypeManage::instance()->registerBeanAssign(id,
                [](void* ptr, const IJson& json)->bool{
                    return static_cast<StudentBeanQVector*>(ptr)->loadJson(json);
            });
        });

    }
};


class StudentBeanQList : public IBeanWare, public QList<StudentBean>, public ITaskInstantUnit<StudentBeanQList>
{
public:
    virtual IJson toJson() const final{
        IJson obj = IJson::array();
        for(const auto& bean : *this){
            obj.emplace_back(bean.toJson());
        }
        return obj;
    }
    virtual bool loadJson(const IJson& json) final
    {
        if(json.is_array()){
            for(const auto& val : json){
                StudentBean bean;
                if(!bean.loadJson(val)){
                    return false;
                }
                this->append(bean);
            }
            return true;
        }
        return false;
    }

private:
    virtual void $task() final{
        static std::once_flag flag;
        std::call_once(flag, [](){
            {
                auto id = IMetaUtil::registerMetaType<StudentBeanQList>();
                IBeanTypeManage::instance()->registerBeanId(id);
                IBeanTypeManage::instance()->registerBeanAssign(id,
                    [](void* ptr, const IJson& json)->bool{
                        return static_cast<StudentBeanQList*>(ptr)->loadJson(json);
                });
            }
            {
                auto id = IMetaUtil::registerMetaType<QList<StudentBean>>();
                IBeanTypeManage::instance()->registerBeanId(id);
                IBeanTypeManage::instance()->registerBeanAssign(id,
                    [](void* ptr, const IJson& json)->bool{
                        return IJsonUtil::fromJson(static_cast<QList<StudentBean>*>(ptr), json);
                });
            }
        });

    }
};
