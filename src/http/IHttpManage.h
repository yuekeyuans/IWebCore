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
    void registInvalidHandler(const QString& name, IHttpInvalidHandlerWare*);

public:
    IHttpAction* getAction(IRequest& request);
    IHttpInvalidHandlerWare* getInvalidHandler(const QString& name) const;
    void printMappingTrace();

    void registerPathValidator(const QString& name, const QString& regexp);
    void registerPathValidator(const QString& name, ValidatorFun fun);

    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

private:
    bool m_isServerStarted{false};
    std::vector<IHttpMappingWare*> m_mappings;
    std::map<QString, IHttpInvalidHandlerWare*> m_invalidHandlers;

    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;
};

$PackageWebCoreEnd
