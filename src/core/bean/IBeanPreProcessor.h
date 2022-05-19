#pragma once

#include "base/IPreProcessorUtil.h"

#define $AsBean(klassName) \
public: \
    $UseMetaRegistration(klassName) \
    $UseGadget(klassName) \
public: \
    operator QString(){ \
        return toString(); \
    } \
    static klassName fromVariantMap(const QMap<QString, QVariant>&map){ \
        klassName bean; \
        IMetaUtil::fromVariantMap(&bean, bean.staticMetaObject, map); \
        return bean; \
    } \
    static klassName fromJson(const QJsonObject& obj){ \
        klassName bean; \
        IMetaUtil::fromJsonObject(&bean, bean.staticMetaObject, obj); \
        return bean; \
    } \
    bool operator==(const klassName& that){ \
        return isEqualTo(&that); \
    } \
    klassName clone(){  \
        return klassName(*this);    \
    }   \
private:

#define $BeanFieldDeclare(type, name) \
    Q_PROPERTY(type name MEMBER name)

//! @note 这里我们使用 空 列表初始化，来保证 基本类型被置为 0.
#define $BeanField_2(type, name) \
    $BeanFieldDeclare(type, name) \
    type name {};

#define $BeanField_3(type, name, value) \
    $BeanFieldDeclare(type, name) \
    type name {value};

#define $BeanField_(N) $BeanField_##N
#define $BeanField_EVAL(N) $BeanField_(N)
#define $BeanField(...) PP_EXPAND( $BeanField_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


#define PP_BEAN_INGNORED_KEY(name)  \
    PP_STRING(iwebcore_bean_field_ignorable_##name)

#define $FieldIgnorable(name) \
    Q_CLASSINFO(PP_BEAN_INGNORED_KEY(name), #name)
