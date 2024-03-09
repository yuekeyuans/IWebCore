#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "web/node/IUrlActionNode.h"

$PackageWebCoreBegin

struct IControllerInfo;

class IControllerInterfaceImpl : public ISingletonUnit<IControllerInterfaceImpl>
{
public:
    IControllerInterfaceImpl() = default;

public:
    static void checkUrlMappings(const IControllerInfo& info);
    static QVector<IUrlActionNode> createMappingLeaves(const IControllerInfo& info);


    // TODO: 俩问题， 一个是把这些东西放到 cpp 中，
    // 二， 调试 url 映射问题
private:
    // 大的检查项目
    void checkMappingOverloadFunctions(const QVector<QMetaMethod>& methods);
    void checkMappingNameAndFunctionIsMatch(const IControllerInfo& info);
    void checkMappingUrlIsValid(const IControllerInfo& info);
    void checkMappingMethodArgsIsValid(const IControllerInfo& info);

    // 检查 url 错误的。
    void chekcUrlErrorCommon(const QString& url);
    void CheckUrlErrorWildCard(const QString url);

    // 检查 函数参数的问题
    void chechMethodSupportedReturnType(const IUrlActionNode& node);
    void checkMethodSupportedParamArgType(const IUrlActionNode& node);
    void checkMethodArgNameIntegrality(const IUrlActionNode& node);
    void checkMethodOfReturnVoid(const IUrlActionNode& node);
    void checkMethodBodyContentArgs(const IUrlActionNode& node);
    void checkMethodParamterWithSuffixProper(const IUrlActionNode& node);
    void checkMethodParamterWithSuffixSet(const IUrlActionNode& node);

private:
    QMap<QString, QString> getStatusCodeInfos(QMap<QString, QString> clsInfos);
};


$PackageWebCoreEnd
