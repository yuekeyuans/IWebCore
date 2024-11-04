#include "IHttpManage.h"
#include "http/net/IRequest.h"
#include "http/mappings/IHttpAction.h"
#include "http/mappings/IHttpMappingWare.h"
#include "http/mappings/IHttpNotFoundAction.h"
#include "http/mappings/IHttpBadRequestAction.h"

$PackageWebCoreBegin

void IHttpManage::setIsServerStarted(bool value)
{
    m_isServerStarted = value;
}

void IHttpManage::registMappingWare(IHttpMappingWare *ware)
{
    m_mappingWares.push_back(ware);
}

IHttpAction *IHttpManage::getAction(IRequest &request)
{
    if(request.isValid()){
        for(IHttpMappingWare* ware : m_mappingWares){
            auto action = ware->getAction(request);
            if(action != nullptr){
                return action;
            }
        }
        return IHttpNotFoundAction::instance();
    }
    return IHttpBadRequestAction::instance();
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

void IHttpManage::travalPrintWareTrace()
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

$PackageWebCoreEnd
