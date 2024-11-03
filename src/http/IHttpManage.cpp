#include "IHttpManage.h"
#include "http/net/IRequest.h"
#include "http/mappings/IHttpMappingWare.h"

$PackageWebCoreBegin

void IHttpManage::setIsServerStarted(bool value)
{
    m_isServerStarted = value;
}

void IHttpManage::registMappingWare(IHttpMappingWare *ware)
{
    m_mappingWares.append(ware);
}

void IHttpManage::registerPathValidator(const QString &name, const QString &regexp)
{
    QRegularExpression exp(regexp);
    if(!exp.isValid()){
        auto info = regexp + " : regular expression is not valid";
        qFatal(info.toUtf8());
    }

    if(m_pathRegValidators.contains(name) || m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    m_pathRegValidators[name] = regexp;
}

void IHttpManage::registerPathValidator(const QString &name, ValidatorFun fun)
{
    if(m_pathFunValidators.contains(name) || m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    m_pathFunValidators[name] = fun;
}

void IHttpManage::travalPrintUrlTree()
{
    for(IHttpMappingWare* ware : instance()->m_mappingWares){
        ware->travelPrint();
    }
}

QString IHttpManage::queryPathRegValidator(const QString &path)
{
    auto inst = instance();
    if(inst->m_pathRegValidators.contains(path)){
        return inst->m_pathRegValidators[path];
    }
    return "";
}

IHttpManage::ValidatorFun IHttpManage::queryPathFunValidator(const QString &path)
{
    auto inst = instance();
    if(inst->m_pathFunValidators.contains(path)){
        return inst->m_pathFunValidators[path];
    }
    return nullptr;
}

IHttpAction *IHttpManage::getAction(IRequest &request)
{
    for(IHttpMappingWare* ware : m_mappingWares){
        auto ret = ware->getActions(request);
        auto size = ret.size();
        if(size == 0){
            continue;
        }else if(size == 1){
            return ret.front();
        }else{
            // 这里返回一个内置的Action
            // TODO: 异常处理
        }
    }
    return nullptr;
}

$PackageWebCoreEnd
