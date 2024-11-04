#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRequest;
class IHttpAction;
class IHttpMappingWare;
class IHttpManage : public ISingletonUnit<IHttpManage>
{
    using ValidatorFun = std::function<bool(const QString&)>;
public:
    IHttpManage() = default;

public:
    void setIsServerStarted(bool);

    void registMappingWare(IHttpMappingWare* ware);
    IHttpAction* getAction(IRequest& request);
    void travalPrintWareTrace();

    void registerPathValidator(const QString& name, const QString& regexp);
    void registerPathValidator(const QString& name, ValidatorFun fun);

    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

private:
    bool m_isServerStarted{false};
    std::vector<IHttpMappingWare*> m_mappingWares;
//    std::map<IHttpStatusCode,

    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;
};

$PackageWebCoreEnd
