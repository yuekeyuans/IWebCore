#include "IAssertManage.h"

#include "IAssertInfoList.h"
#include "base/IToeUtil.h"

$PackageWebCoreBegin

const char FatalType[] = "fatalType";
const char WarningType[] = "warningType";

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
    qDebug().noquote() << "fatal:" << endl
                       << "\tkey:\t" << info.key  << endl
                       << "\tdescribe:\t" <<info.description << endl
                       << "\treason:\t" <<info.reason << endl
                       << "\tsolution:\t" << info.solution;

    if(!extra.isEmpty()){
        qDebug().noquote() << "\textra:\t" << extra;
    }
    qDebug() << endl;

    qFatal(info.reason.toUtf8());
}

void IAssertManage::warn(const QString &name, const QString &extra)
{
    auto key = IToeUtil::trimQuote(name);

    auto inst = instance();
    if(!inst->m_warnInfos.contains(key)){
        qFatal("error get fatal info");
    }

    auto info = inst->m_warnInfos[key];
    qDebug().noquote() << "warning:" <<endl
                       << "\tkey:\t" << info.key  << endl
                       << "\tdescribe:\t" <<info.description << endl
                       << "\treason:\t" <<info.reason << endl
                       << "\tsolution:\t" << info.solution;

    if(!extra.isEmpty()){
        qDebug().noquote() << "\textra:\t" << extra;
    }
    qDebug() << endl;
}

$PackageWebCoreEnd
