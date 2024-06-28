#include "IAssertInterface.h"
//#include "IGlobalAssert.h"
#include "core/base/IMetaUtil.h"

$PackageWebCoreBegin

namespace IAssertInterfaceHelper
{
    QString getOutput(const QString& name, const QPair<QString, QString>& value);
    QString getOutput(const QString& name, const QPair<QString, QString>& value, const IAssertInfo& info);
}

inline void IAssertInterface::fatal(const QString &name)
{
    if(m_fatal.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_fatal[name]);
        qDebug().noquote() << str;
        qFatal(str.toUtf8());
    }
}

inline void IAssertInterface::fatal(const QString &name, const QString &reason)
{
    IAssertInfo info;
    info.reason = reason;
    fatal(name, info);
}

inline void IAssertInterface::fatal(const QString &name, const IAssertInfo &info)
{
    if(m_fatal.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_fatal[name], info);
        qFatal(str.toUtf8());
    }
}

inline void IAssertInterface::warn(const QString &name)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name]);
        qWarning().noquote() << str;
    }
}

inline void IAssertInterface::warn(const QString &name, const QString &reason)
{
    IAssertInfo info;
    info.reason = reason;
    warn(name, info);
}

inline void IAssertInterface::warn(const QString &name, const IAssertInfo &info)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name], info);
        qWarning().noquote() << str;
    }
}

inline void IAssertInterface::debug(const QString &name)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name]);
        qDebug().noquote() << str;
    }
}

inline void IAssertInterface::debug(const QString &name, const QString &reason)
{
    IAssertInfo info;
    info.reason = reason;
    debug(name, info);
}

inline void IAssertInterface::debug(const QString &name, const IAssertInfo &info)
{
    if(m_warn.contains(name)){
        auto str = IAssertInterfaceHelper::getOutput(name, m_warn[name], info);
        qDebug().noquote() << str;
    }
}

inline void IAssertInterface::addFatal(const QString &tag, const QString &info, const QString &solution)
{
    if(m_fatal.contains(tag)){
        auto info = QString("tag, already exist, please check your code. tag: ").append(tag);
        qFatal(info.toUtf8());
    }
    m_fatal[tag] = {info, solution};
}

inline void IAssertInterface::addWarn(const QString &tag, const QString &info, const QString &solution)
{
    if(m_warn.contains(tag)){
        auto info = QString("tag, already exist, please check your code. tag: ").append(tag);
        qFatal(info.toUtf8());
    }
    m_warn[tag] = {info, solution};
}

inline void IAssertInterface::addDebug(const QString &tag, const QString &info, const QString &solution)
{
    if(m_debug.contains(tag)){
        auto info = QString("tag, already exist, please check your code. tag: ").append(tag);
        qFatal(info.toUtf8());
    }
    m_debug[tag] = {info, solution};
}

inline QString IAssertInterfaceHelper::getOutput(const QString& name, const QPair<QString, QString>& value)
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

inline QString IAssertInterfaceHelper::getOutput(const QString& name, const QPair<QString, QString>& value, const IAssertInfo& info)
{
    auto ret = getOutput(name, value);
    ret.append(info);
    return ret;
}

$PackageWebCoreEnd
