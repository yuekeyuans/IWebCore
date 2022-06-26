#pragma once

#include <QtCore>
#include "web/node/IUrlFunctionNode.h"

$PackageWebCoreBegin

class IControllerInterfaceImpl
{
    $UseInstance(IControllerInterfaceImpl);
public:
    static void checkUrlMappings(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);
    static QVector<IUrlFunctionNode> createMappingLeaves(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>& methods);

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
    void chechMethodSupportedReturnType(const IUrlFunctionNode& node);
    void checkMethodSupportedParamArgType(const IUrlFunctionNode& node);
    void checkMethodArgNameIntegrality(const IUrlFunctionNode& node);
    void checkMethodOfReturnVoid(const IUrlFunctionNode& node);
    void checkMethodBodyContentArgs(const IUrlFunctionNode& node);
    void checkMethodParamterWithSuffixProper(const IUrlFunctionNode& node);
    void checkMethodParamterWithSuffixSet(const IUrlFunctionNode& node);

    // 其他调用函数
    QVector<IUrlFunctionNode> createFunctionMappingLeaves(void* handler, const QStringList&, const QMap<QString, QString>& clsInfo, const QVector<QMetaMethod>&methods);
    QVector<QStringList> getMethodMappingInfo(const QMap<QString, QString>&clsInfo);
    QStringList reformClsInfoArgs(const QMap<QString, QString>&, const QStringList &rootPathArgs);
    QMap<QString, QString> getStatusCodeInfos(QMap<QString, QString> clsInfos);
};


$PackageWebCoreEnd
