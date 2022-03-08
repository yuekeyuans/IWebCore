#include "IAssertManage.h"
#include <iostream>
#include <iomanip>
#include "IAssertInfoList.h"
#include "base/IToeUtil.h"
#include "assertion/IAssertDetail.h"

$PackageWebCoreBegin

const char FatalType[] = "fatalType";
const char WarningType[] = "warningType";

namespace IAssertManageHelper{
    void fatal(const IAssertInfo& info, const QString& extra);
    void warn(const IAssertInfo& info, const QString& extra);
    void coutInfo(const IAssertInfo& info, const QString& extra);
    void coutInfo(const QString& tag);
    void coutInfo(const QString& tag, const QString& msg);
}

IAssertManage::IAssertManage()
{
    IAssertInfoList::init();
}

void IAssertManage::registerFatalInfo(const IAssertInfo &info)
{
    auto inst = instance();
    if(inst->m_fatalInfos.contains(info.key)){
        qFatal("error register info");
    }
    inst->m_fatalInfos[info.key] = info;
}

void IAssertManage::registerWarnInfo(const IAssertInfo &info)
{
    auto inst = instance();
    if(inst->m_warnInfos.contains(info.key)){
        qFatal("error register info");
    }
    inst->m_warnInfos[info.key] = info;
}

void IAssertManage::fatal(const QString &name, const QString &extra)
{
    Q_UNUSED(name)
    Q_UNUSED(extra)
#ifdef QT_DEBUG
    auto key = IToeUtil::trimQuote(name);

    auto inst = instance();
    auto keys = inst->m_fatalInfos.keys();
    if(!keys.contains(key)){
        qFatal(extra.toUtf8());
    }

    auto info = inst->m_fatalInfos[key];
    IAssertManageHelper::fatal(info, extra);
#endif
}

void IAssertManage::fatal(const QString &name, const IAssertDetail &detail)
{
    Q_UNUSED(name)
    Q_UNUSED(detail)
#ifdef QT_DEBUG
    const QString& extra = detail.toString();
    fatal(name, extra);
#endif
}

void IAssertManage::warn(const QString &name, const QString &extra)
{
    Q_UNUSED(name)
    Q_UNUSED(extra)
#ifdef QT_DEBUG
    auto key = IToeUtil::trimQuote(name);

    auto inst = instance();
    if(!inst->m_warnInfos.contains(key)){
        qFatal("error get fatal info");
    }

    auto info = inst->m_warnInfos[key];
    IAssertManageHelper::warn(info, extra);
#endif
}

void IAssertManage::warn(const QString &name, const IAssertDetail &detail)
{
    Q_UNUSED(name)
    Q_UNUSED(detail)
#ifdef QT_DEBUG
    const QString& extra = detail.toString();
    warn(name, extra);
#endif
}

inline void IAssertManageHelper::fatal(const IAssertInfo& info, const QString& extra)
{
    Q_UNUSED(info)
    Q_UNUSED(extra)
#ifdef QT_DEBUG
    IAssertManageHelper::coutInfo("Fatal");
    IAssertManageHelper::coutInfo(info, extra);
    qFatal(info.reason.toUtf8());
#endif
}

inline void IAssertManageHelper::warn(const IAssertInfo& info, const QString& extra){
    IAssertManageHelper::coutInfo("Warn");
    IAssertManageHelper::coutInfo(info, extra);
}

inline void IAssertManageHelper::coutInfo(const IAssertInfo& info, const QString& extra)
{
    if(!info.key.isEmpty()){
        IAssertManageHelper::coutInfo("Tag", info.key);
    }
    if(!info.description.isEmpty()){
        IAssertManageHelper::coutInfo("Describe", info.description);
    }
    if(!info.reason.isEmpty()){
        IAssertManageHelper::coutInfo("Reason", info.reason);
    }
    if(!info.solution.isEmpty()){
        IAssertManageHelper::coutInfo("Solution", info.solution);
    }
    if(!extra.isEmpty()){
        IAssertManageHelper::coutInfo("Extra", extra);
    }
}

inline void IAssertManageHelper::coutInfo(const QString& tag)
{
    std::cout << tag.toStdString() << ":" << std::endl;
}

inline void IAssertManageHelper::coutInfo(const QString& tag, const QString& msg)
{
    std::cout << std::setw(8) << tag.toStdString() << ":" << std::setw(0) << msg.toStdString() << std::endl;
}

$PackageWebCoreEnd
