#include "IDebugInterface.h"

$PackageWebCoreBegin

namespace IDebugInterfaceProxy {
    IDebugInterface::Info getInfo(const QList<IDebugInterface::Info>& infos, const QString& tag, bool& ok);
    void outputInfo(const IDebugInterface::Info& info, const QStringList& extra);
}

void IDebugInterface::debug(const QString &tag, const QStringList& extra)
{
    bool ok;
    auto info = IDebugInterfaceProxy::getInfo(this->m_debugInfos, tag, ok);
    if(ok){
        IDebugInterfaceProxy::outputInfo(info, extra);
    }else{
        qFatal("error tag with debug");
    }
}

void IDebugInterface::warn(const QString &tag, const QStringList& extra)
{
    bool ok;
    auto info = IDebugInterfaceProxy::getInfo(this->m_debugInfos, tag, ok);
    if(ok){
        IDebugInterfaceProxy::outputInfo(info, extra);
    }else{
        qFatal("error tag with debug");
    }
}

void IDebugInterface::error(const QString &tag, const QStringList& extra)
{
    bool ok;
    auto info = IDebugInterfaceProxy::getInfo(this->m_debugInfos, tag, ok);
    if(ok){
        IDebugInterfaceProxy::outputInfo(info, extra);
    }else{
        qFatal("error tag with debug");
    }
}

void IDebugInterface::fatal(const QString &tag, const QStringList& extra)
{
    bool ok;
    auto info = IDebugInterfaceProxy::getInfo(this->m_debugInfos, tag, ok);
    if(ok){
        IDebugInterfaceProxy::outputInfo(info, extra);
        fatal(info.reason);
    }else{
        qFatal("error tag with debug");
    }
}

void IDebugInterface::loadConfigs()
{
    auto obj = jsonFormatedInfo();
    static const QMap<QString, QList<Info>*> map = {
        {"debug", &m_debugInfos},
        {"warn", &m_warnInfos},
        {"error", &m_errorInfos},
        {"fatal", &m_fatalInfos}
    };

    const auto& keys = map.keys();
    for(const QString key : keys){
        if(obj.contains(key)){
            auto infos = map[key];
            auto array = obj[key].toArray();
            for(auto value : array){
                auto info = value.toObject();
                infos->append({info["tag"].toString(), info["reason"].toString(), info["solution"].toString() });
            }
        }
    }
}

IDebugInterface::Info IDebugInterfaceProxy::getInfo(const QList<IDebugInterface::Info>& infos, const QString& tag, bool& ok)
{
    for(const auto& info : infos){
        if(info.tag == tag){
            ok = true;
            return info;
        }
    }
    ok = false;
    return {};
}

void IDebugInterfaceProxy::outputInfo(const IDebugInterface::Info& info, const QStringList& extra)
{
    qDebug() << info.tag << endl
                 << info.reason << endl
                 << info.solution << endl
             << extra.join(" ");
}

$PackageWebCoreEnd
