#include "IAssertManage.h"
#include <iostream>
#include <iomanip>
#include "IAssertInfoList.h"
#include "base/IToeUtil.h"

$PackageWebCoreBegin

const char FatalType[] = "fatalType";
const char WarningType[] = "warningType";

namespace IAssertManageHelper{

    QString detailToString(const QMap<IAssertDetail::Type, QString>& info);

    void fatal(const IAssertInfo& info, const QString& extra);
    void warn(const IAssertInfo& info, const QString& extra);
    void coutInfo(const IAssertInfo& info, const QString& extra);
    void coutInfo(const QString& tag);
    void coutInfo(const QString& tag, const QString& msg);
}

void IAssertDetail::setDetail(IAssertDetail::Type type, const QString &info)
{
    m_detailInfo[type] = info;
}

QString &IAssertDetail::operator [](IAssertDetail::Type type)
{
    return m_detailInfo[type];
}

QString IAssertDetail::toString()
{
    return IAssertManageHelper::detailToString(m_detailInfo);
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
    auto key = IToeUtil::trimQuote(name);

    auto inst = instance();
    auto keys = inst->m_fatalInfos.keys();
    if(!keys.contains(key)){
        qFatal(extra.toUtf8());
    }

    auto info = inst->m_fatalInfos[key];
    IAssertManageHelper::fatal(info, extra);
}

void IAssertManage::warn(const QString &name, const QString &extra)
{
    auto key = IToeUtil::trimQuote(name);

    auto inst = instance();
    if(!inst->m_warnInfos.contains(key)){
        qFatal("error get fatal info");
    }

    auto info = inst->m_warnInfos[key];
    IAssertManageHelper::warn(info, extra);
}

inline QString IAssertManageHelper::detailToString(const QMap<IAssertDetail::Type, QString>& info)
{
    auto keys = info.keys();
    QStringList ret;
    for(auto key : keys){
        QString name = QMetaEnum::fromType<IAssertDetail::Type>().valueToKey(key);
        ret.append(name + ": " + info[key]);
    }
    return ret.join(", ");
}

inline void IAssertManageHelper::fatal(const IAssertInfo& info, const QString& extra)
{
    IAssertManageHelper::coutInfo("Fatal");
    IAssertManageHelper::coutInfo(info, extra);
    qFatal(info.reason.toUtf8());
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
