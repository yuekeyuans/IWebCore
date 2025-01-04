#pragma once

#include "http/controller/IHttpControllerAction.h"

$PackageWebCoreBegin

struct IHttpMethodMappingInfo
{
public:
    IHttpMethodMappingInfo(const QString& key);

public:
    int m_index;
    QString m_funName;
    std::vector<IHttpPathFragment> m_fragments;
    IHttpMethod m_method;
};

class IHttpControllerInfo
{
public:
    IHttpControllerInfo(void *handler, const QString &className,
                              const QMap<QString, QString> &classInfo,
                              const QVector<QMetaMethod> &methods);
private:
    void parseMapppingInfos();
    void parseMappingLeaves();
    void parseRootPaths();

private:
    std::vector<IHttpPathFragment> parseFragments(const QString& path);
    IMethodNode getHttpMethodNode(const QString& name);

private:
    void checkPathArgumentMatch();
    void checkMappingOverloadFunctions();
    void checkMappingNameAndFunctionIsMatch();

private:
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

private:
    std::vector<IHttpPathFragment> rootFragments;
    QVector<IHttpMethodMappingInfo> m_mappingInfos;

public:
    QVector<IHttpControllerAction> m_actionNodes;
};

$PackageWebCoreEnd
