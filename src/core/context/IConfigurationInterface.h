//#pragma once

//#include "IContextManage.h"
//#include "core/base/IHeaderUtil.h"
//#include "core/unit/IRegisterInstanceUnit.h"

//$PackageWebCoreBegin


///**
// * 系统 配置， 是指 环境变量 和 框架运行使用的 变量， 比如说是否使用 session, 等内容
// * 而 Application 变量，则是指 用户自定义并且使用的变量, 比如说 数据库配置等内容
// *
// * 系统配置和Application 配置有冲突的时候，Application 变量优先。
// */
//// 这个是直接注册的， 但是好像没人用它， TODO: 看看之后是否需要重构成 经过task 的
//template<typename T, bool enabled = true, const char* groupName = ApplicationConfigurationGroup >
//class IConfigurationInterface : IRegisterInstanceUnit<T, enabled>
//{
//protected:
//    IConfigurationInterface() = default;
//    virtual ~IConfigurationInterface() = default;

//public:
//    virtual QString getGroupName() const { return QString(groupName); };
//    virtual QJsonObject getConfigure() const = 0;

//private:
//    virtual void registerToBase() override;

//private:
//    friend class IRegisterInstanceUnit<T, enabled>;
//};


//template<typename T, bool enabled, const char *groupName>
//void IConfigurationInterface<T, enabled, groupName>::registerToBase() {
//    auto inst = T::instance();
//    QString group = inst->getGroupName();
//    QJsonObject obj = inst->getConfigure();
//    IContextManage::registerConfiguration(group, obj);
//}

//template<typename T, const char* name>
//using IConfigurationGroupInterface = IConfigurationInterface<T, true, name>;

//template<typename T, bool enabled = true>
//using IApplicationConfigurationInterface = IConfigurationInterface<T, enabled, ApplicationConfigurationGroup>;

//template<typename T, bool enabled = true>
//using ISystemConfigurationInterface = IConfigurationInterface<T, enabled, SystemConfigurationGroup>;

////template<typename T, bool enabled = true>
////using IUserConfigurationInterface = IConfigurationInterface<T, enabled, UserConfigurationGroup>;

//$PackageWebCoreEnd
