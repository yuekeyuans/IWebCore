#include "IHttpManage.h"
#include "http/net/IRequest.h"
#include "http/mappings/IHttpAction.h"
#include "http/mappings/IHttpMappingWare.h"
#include "http/mappings/IHttpNotFoundAction.h"
#include "http/mappings/IHttpBadRequestAction.h"
#include "http/mappings/IHttpOptionsMethodAction.h"
#include "http/mappings/IHttpInvalidRequestAction.h"
#include "http/invalid/IHttpInvalidHandlerInterface.h"

$PackageWebCoreBegin

void IHttpManage::setIsServerStarted(bool value)
{
    m_isServerStarted = value;
}

void IHttpManage::registMapping(IHttpMappingWare *ware)
{
    m_mappings.push_back(ware);
}

void IHttpManage::registInvalidHandler(const std::string& name, IHttpInvalidHandlerWare * ware)
{
    m_invalidHandlers[&name] = ware;
}

IHttpAction *IHttpManage::getAction(IRequest &request)
{
    if(request.isValid()){
        if(request.method() == IHttpMethod::OPTIONS){
            return IHttpOptionsMethodAction::instance();
        }
        for(IHttpMappingWare* ware : m_mappings){
            auto action = ware->getAction(request);
            if(action != nullptr){
                return action;
            }
        }
        return IHttpNotFoundAction::instance();
    }
    return IHttpInvalidRequestAction::instance();
}

IHttpInvalidHandlerWare *IHttpManage::getInvalidHandler(const std::string &name) const
{
    if(m_invalidHandlers.find(&name) != m_invalidHandlers.end()){
        return m_invalidHandlers.at(&name);
    }
    return nullptr;
}

void IHttpManage::registerPathValidator(const QString &name, ValidatorFun fun)
{
    if(m_pathFunValidators.contains(name) || m_pathFunValidators.contains(name)){
        auto info = name + " validator already registered";
        qFatal(info.toUtf8());
    }

    m_pathFunValidators[name] = fun;
}

void IHttpManage::printMappingTrace()
{
    for(IHttpMappingWare* ware : m_mappings){
        ware->travelPrint();
    }
}

IHttpManage::ValidatorFun IHttpManage::queryPathFunValidator(const QString &path)
{
    if(m_pathFunValidators.contains(path)){
        return m_pathFunValidators[path];
    }
    return nullptr;
}

$PackageWebCoreEnd
