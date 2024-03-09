#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "web/node/IUrlActionNode.h"

$PackageWebCoreBegin

struct IControllerInfo;

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
    void checkUrlMappings(const IControllerInfo& info);
    QVector<IUrlActionNode> createMappingLeaves(const IControllerInfo& info);

//private:
    void checkMappingOverloadFunctions(const QVector<QMetaMethod>& methods);
    void checkMappingNameAndFunctionIsMatch(const IControllerInfo& info);
    void checkMappingUrlIsValid(const IControllerInfo& info);
    void checkMappingMethodArgsIsValid(const IControllerInfo& info);

    void chekcUrlErrorCommon(const QString& url);
    void CheckUrlErrorWildCard(const QString url);

    void chechMethodSupportedReturnType(const IUrlActionNode& node);
    void checkMethodSupportedParamArgType(const IUrlActionNode& node);
    void checkMethodArgNameIntegrality(const IUrlActionNode& node);
    void checkMethodOfReturnVoid(const IUrlActionNode& node);
    void checkMethodBodyContentArgs(const IUrlActionNode& node);
    void checkMethodParamterWithSuffixProper(const IUrlActionNode& node);
    void checkMethodParamterWithSuffixSet(const IUrlActionNode& node);

    bool isBeanType(const QString&);
    bool isSpecialTypes(const QString&);
    bool isParamNameWithSuffix(const QString& paramName);
    bool isIgnoreParamCheckFunction(const QString& funName, const QMap<QString, QString>& clsInfo);

    QVector<MappingInfo> getMethodMappingInfo(const QMap<QString, QString> &clsInfo);
    QStringList toNormalUrl(const QString& url, const QStringList& prefix);
    QVector<IUrlActionNode> createFunctionMappingLeaves(const IControllerInfo& info, const MappingInfo& mapping);
}

$PackageWebCoreEnd
