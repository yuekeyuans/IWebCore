#pragma once

#include "IConfigurationWirePreProcessor.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/bean/IBeanPreProcessor.h"

#define $AsConfiguration(klassName) \
    $UseInstance(klassName)

#define $UseConfig(klassName) \
    Q_INVOKABLE void IWebPreRun_ResolveConfigField()    \
    {   \
        auto clsInfo = IMetaUtil::getMetaClassInfoMap(staticMetaObject);    \
        auto props = IMetaUtil::getMetaProperties(staticMetaObject);    \
        bool ok;    \
        IContextManage::getConfigBean(this, clsInfo, props, &ok);    \
    }

#define $ConstructConfig() \
    this->IWebPreRun_ResolveConfigField();


// TODO: 之后添加 optional, 像 auto wire 系统一样
// int
#define $IntConfiger_1(name)    \
    int name(){ \
        bool ok;    \
        int value = IConfigurationManage::getIntValue(#name, &ok);   \
        return ok ? value : 0;  \
    }

#define $IntConfiger_2(name, path)    \
    int name(){ \
        bool ok;    \
        int value = IConfigurationManage::getIntValue(#path, &ok);   \
        return ok ? value : 0;  \
    }

#define $IntConfiger_3(name, defaultVal, path)    \
    int name(){ \
        bool ok;    \
        int value = IConfigurationManage::getIntValue(#path, &ok);   \
        return ok ? value : defaultVal;  \
    }

#define $IntConfiger_(N) $IntConfiger_##N
#define $IntConfiger_EVAL(N) $IntConfiger_(N)
#define $IntConfiger(...) PP_EXPAND( $IntConfiger_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// double

#define $DoubleConfiger_1(name)    \
    double name(){ \
        bool ok;    \
        double value = IConfigurationManage::getDoubleValue(#name, &ok);   \
        return ok ? value : 0;  \
    }

#define $DoubleConfiger_2(name, path)    \
    double name(){ \
        bool ok;    \
        double value = IConfigurationManage::getDoubleValue(#path, &ok);   \
        return ok ? value : 0;  \
    }

#define $DoubleConfiger_3(name, defaultVal, path)    \
    double name(){ \
        bool ok;    \
        double value = IConfigurationManage::getDoubleValue(#path, &ok);   \
        return ok ? value : defaultVal;  \
    }

#define $DoubleConfiger_(N) $DoubleConfiger_##N
#define $DoubleConfiger_EVAL(N) $DoubleConfiger_(N)
#define $DoubleConfiger(...) PP_EXPAND( $DoubleConfiger_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// bool

#define $BoolConfiger_1(name)    \
    bool name(){ \
        bool ok;    \
        bool value = IConfigurationManage::getBoolValue(#name, &ok);   \
        return ok ? value : 0;  \
    }

#define $BoolConfiger_2(name, path)    \
    bool name(){ \
        bool ok;    \
        bool value = IConfigurationManage::getBoolValue(#path, &ok);   \
        return ok ? value : 0;  \
    }

#define $BoolConfiger_3(name, defaultVal, path)    \
    bool name(){ \
        bool ok;    \
        bool value = IConfigurationManage::getBoolValue(#path, &ok);   \
        return ok ? value : defaultVal;  \
    }

#define $BoolConfiger_(N) $BoolConfiger_##N
#define $BoolConfiger_EVAL(N) $BoolConfiger_(N)
#define $BoolConfiger(...) PP_EXPAND( $BoolConfiger_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// string

#define $StringConfiger_1(name)    \
    QString name(){ \
        bool ok;    \
        QString value = IConfigurationManage::getStringValue(#name, &ok);   \
        return ok ? value : "";  \
    }

#define $StringConfiger_2(name, path)    \
    QString name(){ \
        bool ok;    \
        QString value = IConfigurationManage::getStringValue(#path, &ok);   \
        return ok ? value : "";  \
    }

#define $StringConfiger_3(name, defaultVal, path)    \
    QString name(){ \
        bool ok;    \
        QString value = IConfigurationManage::getStringValue(#path, &ok);   \
        return ok ? value : #defaultVal;  \
    }

#define $StringConfiger_(N) $StringConfiger_##N
#define $StringConfiger_EVAL(N) $StringConfiger_(N)
#define $StringConfiger(...) PP_EXPAND( $StringConfiger_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

// set system value



