#pragma once

#include <QtCore>
#include "web/node/IUrlActionNode.h"

$PackageWebCoreBegin

class IControllerInterfaceImpl
{
    $UseInstance(IControllerInterfaceImpl);
public:
    static void checkUrlMappings(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    static QVector<IUrlActionNode> createMappingLeaves(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);

private:
    // 大的检查项目
    void checkMappingOverloadFunctions(const QVector<QMetaMethod>& methods);
    void checkMappingNameAndFunctionIsMatch(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    void checkMappingUrlIsValid(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    void checkMappingMethodArgsIsValid(void* handler, const QMap<QString, QString>& clsInfo,  const QVector<QMetaMethod>& methods);

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

    // 其他调用函数
    QVector<IUrlActionNode> createFunctionMappingLeaves(void* handler, const QStringList&, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
    QVector<QStringList> getMethodMappingInfo(const QMap<QString, QString>&clsInfo);
    QStringList reformClsInfoArgs(const QMap<QString, QString>&, const QStringList &rootPathArgs);
    QMap<QString, QString> getStatusCodeInfos(QMap<QString, QString> clsInfos);
};


$PackageWebCoreEnd
