#include "IAssertInterface.h"
#include "IGlobalAssert.h"
#include "base/IMetaUtil.h"

$PackageWebCoreBegin

namespace IAssertInterfaceHelper
{
    QString getOutput(const QString& name, const QPair<QString, QString>& value);
    QString getOutput(const QString& name, const QPair<QString, QString>& value, const IAssertInfo& info);
}

void IAssertInterface::load(const QString& klassName)
{
    std::call_once(flag, [&](){
        loadFromFunction();

        auto value = this->loadFromJsonString();
        if(!value.isEmpty()){
            bool ok;
            auto json = IJsonUtil::toJsonObject(value, &ok);
            if(!ok){
                IAssertInfo info;
                info.className = klassName;
                IGlobalAssert::instance()->fatal("Assert_Load_Json_Error", info);
            }

            QStringList types = json.keys();
            for(const auto& type : types){
                auto obj = json[type].toObject();
                auto keys = obj.keys();
                for(const auto& key : keys){
                    auto array = obj[key].toArray();
                    if(array.size() == 1){
                        if(type == "fatal"){
                            addFatal(key, array.first().toString());
                        }else if(type == "warn"){
                            addWarn(key, array.first().toString());
                        }else{
                            addDebug(key, array.first().toString());
                        }
                    }else if(array.size() == 2){
                        if(type == "fatal"){
                            addFatal(key, array.first().toString(), array.last().toString());
                        }else if(type == "warn"){
                            addWarn(key, array.first().toString(), array.last().toString());
                        }else{
                            addDebug(key, array.first().toString(), array.last().toString());
                        }
                    }
                }
            }
        }
    });
}

QString IAssertInterface::loadFromJsonString()
{
    return "";
}

void IAssertInterface::loadFromFunction()
{
}

void IAssertInterface::fatal(const QString &name)
{
    if(m_fatal.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_fatal[name]);
        qDebug().noquote() << str;
        qFatal(str.toUtf8());
    }
}

void IAssertInterface::fatal(const QString &name, const IAssertInfo &info)
{
    if(m_fatal.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_fatal[name], info);
//        qDebug().noquote() << str;
        qFatal(str.toUtf8());
    }
}

void IAssertInterface::warn(const QString &name)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name]);
        qWarning().noquote() << str;
    }
}

void IAssertInterface::warn(const QString &name, const IAssertInfo &info)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name], info);
        qWarning().noquote() << str;
    }
}

void IAssertInterface::debug(const QString &name)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name]);
        qDebug().noquote() << str;
    }
}

void IAssertInterface::debug(const QString &name, const IAssertInfo &info)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name], info);
        qDebug().noquote() << str;
    }
}

void IAssertInterface::addFatal(const QString &tag, const QString &info, const QString &solution)
{
    if(m_fatal.contains(tag)){
        auto info = QString("tag, already exist, please check your code. tag: ").append(tag);
        qFatal(info.toUtf8());
    }
    m_fatal[tag] = {info, solution};
}

void IAssertInterface::addWarn(const QString &tag, const QString &info, const QString &solution)
{
    if(m_warn.contains(tag)){
        auto info = QString("tag, already exist, please check your code. tag: ").append(tag);
        qFatal(info.toUtf8());
    }
    m_warn[tag] = {info, solution};
}

void IAssertInterface::addDebug(const QString &tag, const QString &info, const QString &solution)
{
    if(m_debug.contains(tag)){
        auto info = QString("tag, already exist, please check your code. tag: ").append(tag);
        qFatal(info.toUtf8());
    }
    m_debug[tag] = {info, solution};
}

QString IAssertInterfaceHelper::getOutput(const QString& name, const QPair<QString, QString>& value)
{
    QString ret;
    ret.append("[TAG] ").append(name);
    if(!value.first.isEmpty()){
        ret.append(" [INFO] ").append(value.first);
    }
    if(!value.second.isEmpty()){
        ret.append(" [SOLUTION] ").append(value.second);
    }
    return ret;
}

QString IAssertInterfaceHelper::getOutput(const QString& name, const QPair<QString, QString>& value, const IAssertInfo& info)
{
    auto ret = getOutput(name, value);
    ret.append(info);
    return ret;
}

$PackageWebCoreEnd
