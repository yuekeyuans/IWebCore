#pragma once

#include "core/unit/ISingletonUnit.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRequest;
class IHttpAction;
class IHttpMappingWare;
class IHttpInvalidHandlerWare;
class IHttpManage : public ISingletonUnit<IHttpManage>
{
    using ValidatorFun = std::function<bool(const QString&)>;
public:
    IHttpManage() = default;

public:
    void setIsServerStarted(bool);

    void registMapping(IHttpMappingWare* ware);
    void registInvalidHandler(const std::string& name, IHttpInvalidHandlerWare*);

public:
    IHttpAction* getAction(IRequest& request);
    IHttpInvalidHandlerWare* getInvalidHandler(const std::string& name) const;
    void printMappingTrace();

    void registerPathValidator(const QString& name, ValidatorFun fun);
    ValidatorFun queryPathFunValidator(const QString& path);

private:
    bool m_isServerStarted{false};
    std::vector<IHttpMappingWare*> m_mappings;
    std::map<const std::string*, IHttpInvalidHandlerWare*> m_invalidHandlers;

    QMap<QString, ValidatorFun> m_pathFunValidators;
};

$PackageWebCoreEnd
