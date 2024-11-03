#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"

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

    void registerPathValidator(const QString& name, const QString& regexp);
    void registerPathValidator(const QString& name, ValidatorFun fun);

    static void travalPrintUrlTree();
    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

    IHttpAction* getAction(IRequest& request);

private:
    bool m_isServerStarted{false};
    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;


private:
    QVector<IHttpMappingWare*> m_mappingWares;
};

$PackageWebCoreEnd
