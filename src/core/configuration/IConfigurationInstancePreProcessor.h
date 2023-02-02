#pragma once

#include "core/base/IPreProcessorUtil.h"

#define IConfigInstance_2(klassName, configGroup)                                       \
class klassName                                                                         \
{                                                                                       \
private:                                                                                \
    klassName(){                                                                        \
        QJsonObject config = configure();                                               \
        auto name = getGroupName();                                                     \
        IConfigurationManage::registerConfiguration(name, config);                      \
    }                                                                                   \
                                                                                        \
    QString getGroupName(){                                                             \
        return PP_STRING(configGroup);                                                  \
    }                                                                                   \
    QJsonObject configure();                                                            \
                                                                                        \
public:                                                                                 \
    static klassName* instance(){                                                       \
        static klassName inst;                                                          \
        return &inst;                                                                   \
    }                                                                                   \
                                                                                        \
private:                                                                                \
    const QString DEAULT_CONFIG_GROUP {"Application"};                                  \
};                                                                                      \
                                                                                        \
static klassName* iweb_ ## klassName ## _instance = klassName::instance();              \
                                                                                        \
QJsonObject klassName::configure()

#define IConfigInstance_1(klassName)                                                    \
class klassName                                                                         \
{                                                                                       \
private:                                                                                \
    klassName(){                                                                        \
        QJsonObject config = configure();                                               \
        auto name = getGroupName();                                                     \
        IConfigurationManage::registerConfiguration(name, config);                      \
    }                                                                                   \
                                                                                        \
    QString getGroupName(){                                                             \
        return DEAULT_CONFIG_GROUP;                                                     \
    }                                                                                   \
    QJsonObject configure();                                                            \
                                                                                        \
public:                                                                                 \
    static klassName* instance(){                                                       \
        static klassName inst;                                                          \
        return &inst;                                                                   \
    }                                                                                   \
                                                                                        \
private:                                                                                \
    const QString DEAULT_CONFIG_GROUP {"Application"};                                  \
};                                                                                      \
                                                                                        \
static klassName* iweb_ ## klassName ## _instance = klassName::instance();              \
                                                                                        \
QJsonObject klassName::configure()

#define IConfigInstance_(N) IConfigInstance_##N
#define IConfigInstance_EVAL(N) IConfigInstance_(N)
#define IConfigInstance(...) PP_EXPAND( IConfigInstance_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// string config
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define IConfigStringInstance_2(klassName, configGroup)                                 \
class klassName                                                                        	\
{                                                                                      	\
private:                                                                               	\
    klassName(){                                                                       	\
        QJsonObject config = configure();                                              	\
        auto name = getGroupName();                                                    	\
        IConfigurationManage::registerConfiguration(name, config);                      \
    }                                                                                  	\
                                                                                        \
    QString getGroupName(){                                                            	\
        return PP_STRING(configGroup);                                                 	\
    }                                                                                  	\
    QJsonObject configure(){                                                           	\
        return QJsonDocument::fromJson(configureByContent().toUtf8()).object();        	\
    }                                                                                  	\
                                                                                        \
    QString configureByContent();                                                      	\
                                                                                        \
public:                                                                                	\
    static klassName& instance(){                                                      	\
        static klassName* inst = new klassName();                                      	\
        return *inst;                                                                  	\
    }                                                                                  	\
                                                                                        \
private:                                                                               	\
    const QString DEAULT_CONFIG_GROUP {"Application"};                                  \
};                                                                                     	\
                                                                                        \
static klassName* iweb_ ## klassName ## _instance = &klassName::instance();             \
                                                                                        \
QString klassName::configureByContent()


#define IConfigStringInstance_1(klassName)                                              \
class klassName                                                                        	\
{                                                                                      	\
private:                                                                               	\
    klassName(){                                                                       	\
        QJsonObject config = configure();                                              	\
        auto name = getGroupName();                                                    	\
        IConfigurationManage::registerConfiguration(name, config);                      \
    }                                                                                  	\
                                                                                        \
    QString getGroupName(){                                                            	\
        return DEAULT_CONFIG_GROUP;                                                    	\
    }                                                                                  	\
    QJsonObject configure(){                                                           	\
        return QJsonDocument::fromJson(configureByContent().toUtf8()).object();        	\
    }                                                                                  	\
                                                                                        \
    QString configureByContent();                                                      	\
                                                                                        \
public:                                                                                	\
    static klassName& instance(){                                                      	\
        static klassName* inst = new klassName();                                      	\
        return *inst;                                                                  	\
    }                                                                                  	\
                                                                                        \
private:                                                                               	\
    const QString DEAULT_CONFIG_GROUP {"Application"};                                  \
};                                                                                     	\
                                                                                        \
static klassName* iweb_ ## klassName ## _instance = &klassName::instance();             \
                                                                                        \
QString klassName::configureByContent()

#define IConfigStringInstance_(N) IConfigStringInstance_##N
#define IConfigStringInstance_EVAL(N) IConfigStringInstance_(N)
#define IConfigStringInstance(...) PP_EXPAND( IConfigStringInstance_EVAL(PP_EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )
