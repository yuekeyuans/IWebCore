#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/middleware/IMiddleWare.h"
#include "web/middleware/IInterceptorWare.h"
#include "web/middleware/IProcessorWare.h"
#include "web/node/IUrlActionNode.h"
#include "web/node/IStatusActionNode.h"

#include "IControllerRouteMapping.h"
#include "IControllerResourceMapping.h"
#include "IControllerFolderMapping.h"

$PackageWebCoreBegin

class IRequest;
class IControllerManage : public ISingletonUnit<IControllerManage>
{
    using ValidatorFun = bool (*)(const QString&);
public:
    IControllerManage() = default;

public:
    static void setIsServerStarted(bool);

    // TODO: 考虑 将函数换一些好用的名字
    void registerStatusActionNode(IStatusActionNode node);
    void registerStatusActionNodes(const QVector<IStatusActionNode>& statusNodes);

    void unRegisterStatusActionNode(const IStatusActionNode& node);
    void unRegisterStatusActionNodes(const QVector<IStatusActionNode>& statusNodes);

    void registerUrlActionNode(IUrlActionNode node);
    void registerUrlActionNodes(const QVector<IUrlActionNode>& functionNodes);

    void unRegisterUrlActionNode(IUrlActionNode node);
    void unRegisterUrlActionNodes(const QVector<IUrlActionNode>& functionNodes);

    void registerStaticFiles(const QString& path, const QString& prefix);

    void registerPathValidator(const QString& name, const QString& regexp);
    void registerPathValidator(const QString& name, ValidatorFun fun);

    // TODO: 这里需要考虑添加到 global 和 local 的两种情形，之后添加上来，作为 AOP 的一部分。
    static void registerPreProcessor(IProcessorWare* middleWare);
    static void registerPostProcessor(IProcessorWare* middleWare);
    static void registerPreInterceptor(IInterceptorWare* middleWare);
    static void registerPostInterceptor(IInterceptorWare* middleWare);

    static void travalPrintUrlTree();
    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

    bool isUrlActionNodeEnabled() const;
    IUrlActionNode* getUrlActionNode(IRequest& request);

    static IStatusActionNode* getStatusActionNode(IHttpStatus status);

    bool isStaticFileActionPathEnabled();
    QString getStaticFileActionPath(const IRequest& request);
    QStringList getStaticFolderActionPath(const IRequest& request);

    static bool preIntercept(IRequest& request, IResponse& response);
    static bool postIntercept(IRequest& request, IResponse& response);
    static bool preProcess(IRequest& request, IResponse& response);
    static bool postProcess(IRequest& request, IResponse& response);

private:
    static QVector<IUrlActionNode*> queryFunctionNodes(IControllerRouteMapping* parentNode, const QStringList& fragments, IHttpMethod method);
    static QMap<QString, QByteArray> getPathVariable(void* node, const QStringList& fragments);

    // 这里实现 url 时 需要防止  /<name>/<name>/  这种重复类型的 url
    static bool checkUrlDuplicateName(const IUrlActionNode* node);

    static void checkRegisterAvalible();    // 检查是否能够注册

private:
    bool m_isServerStarted{false};
    IControllerRouteMapping m_urlMapppings;
    IControllerResourceMapping m_resourceMappings;
    IControllerFolderMapping m_folderMappings;

    QMap<IHttpStatus, IStatusActionNode> m_statusMappings;
    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;

    QVector<IProcessorWare*> m_preProcessors;
    QVector<IProcessorWare*> m_postProcessors;

    QVector<IInterceptorWare*> m_preInterceptors;
    QVector<IInterceptorWare*> m_postInterceptors;
};

$PackageWebCoreEnd
