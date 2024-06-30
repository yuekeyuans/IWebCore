#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/base/IUrlActionNode.h"

$PackageWebCoreBegin

struct IHttpControllerInfo;

namespace IControllerInterfaceHelper
{
    struct MappingInfo
    {
        QString funName;
        QStringList path;
        IHttpMethod method;
        int index;
    };

//public:
    void checkUrlMappings(const IHttpControllerInfo& info);
//private:
    void checkMappingOverloadFunctions(const QVector<QMetaMethod>& methods);
    void checkMappingNameAndFunctionIsMatch(const IHttpControllerInfo& info);
    void checkMappingUrlIsValid(const IHttpControllerInfo& info);
    void checkMappingMethodArgsIsValid(const IHttpControllerInfo& info);

    void chekcUrlErrorCommon(const QString& url);
    void CheckUrlErrorWildCard(const QString url);

    void chechMethodSupportedReturnType(const IUrlActionNode& node);
    void checkMethodSupportedParamArgType(const IUrlActionNode& node);
    void checkMethodOfReturnVoid(const IUrlActionNode& node);
    void checkMethodBodyContentArgs(const IUrlActionNode& node);
    void checkMethodParamterWithSuffixProper(const IUrlActionNode& node);

//public:
    QVector<IUrlActionNode> createMappingLeaves(const IHttpControllerInfo& info);
//private:
    bool isBeanType(const QString&);
    bool isSpecialTypes(const QString&);

    QVector<MappingInfo> getMethodMappingInfo(const QMap<QString, QString> &clsInfo);
    QStringList toNormalUrl(const QString& url, const QStringList& prefix);
    QVector<IUrlActionNode> createFunctionMappingLeaves(const IHttpControllerInfo& info, const MappingInfo& mapping);
}

$PackageWebCoreEnd
