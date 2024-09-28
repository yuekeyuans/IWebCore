#pragma once

#include "core/util/IPreProcessorUtil.h"

#define $BeanFieldDeclare(type, name) \
    Q_PROPERTY(type name MEMBER name WRITE $write_##name##_value)   \
    Q_INVOKABLE void* $get_ ## name ## _ptr(){ return & name; }     \
    void $write_##name##_value(const type & value){this-> name = value; }

#define $BeanField_2(type, name) \
    $BeanFieldDeclare(type, name) \
    type name {};

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

//#define PP_BEAN_INGNORED_KEY(name)  \
//    PP_STRING(iwebcore_bean_field_ignorable_##name)

//#define $FieldIgnorable(name) \
//    Q_CLASSINFO(PP_BEAN_INGNORED_KEY(name), #name)

#define $AsBeanList(klassName)                                                                         \
class klassName ## List : public QList< klassName >, public IBeanInterface< klassName ## List >        \
{                                                                                                      \
    Q_GADGET                                                                                           \
public:                                                                                                \
    virtual IJson toJson(bool *ok) const final {                                                       \
        IJson json = IJson::array();                                                                   \
        for(const klassName & bean : *this){                                                           \
            json.push_back(bean.toJson(ok));                                                           \
            if(ok != nullptr && *ok ==false){                                                          \
                return json;                                                                           \
            }                                                                                          \
        }                                                                                              \
        return json;                                                                                   \
    }                                                                                                  \
    virtual bool loadJson(const IJson &value) final{                                                   \
        if(value.is_null()){ return true; }                                                            \
        if(!value.is_array()){ return false; }                                                         \
        for(const IJson& value : value){                                                               \
            klassName bean;                                                                            \
            if(!bean.loadJson(value)){                                                                 \
                return false;                                                                          \
            }                                                                                          \
            this->append(bean);                                                                        \
        }                                                                                              \
        return true;                                                                                   \
    }                                                                                                  \
};
