#pragma once

#include "base/IHeaderUtil.h"
#include "base/IPreProcessorUtil.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/biscuits/IHttpStatus.h"
#include "web/middleware/IMiddleWare.h"
#include "web/middleware/IInterceptorWare.h"
#include "web/middleware/IProcessorWare.h"
#include "web/node/IUrlActionNode.h"
#include "web/node/IStatusActionNode.h"

#include "IControllerRouteNode.h"
#include "IControllerFileNode.h"

$PackageWebCoreBegin
class IRequest;
class IControllerManage
{
    Q_DISABLE_COPY(IControllerManage)
    $UseInstance(IControllerManage)
private:
    IControllerManage();
    ~IControllerManage() = default;

public:
    using ValidatorFun = bool (*)(const QString&);

    static void setIsServerStarted(bool);

    // TODO: 考虑 将函数换一些好用的名字
    static void registerStatusActionNode(IStatusActionNode node);
    static void registerStatusActionNodes(const QVector<IStatusActionNode>& statusNodes);

    static void unRegisterStatusActionNode(const IStatusActionNode& node);
    static void unRegisterStatusActionNodes(const QVector<IStatusActionNode>& statusNodes);

    static void registerUrlActionNode(IUrlActionNode node);
    static void registerUrlActionNodes(const QVector<IUrlActionNode>& functionNodes);

    static void unRegisterUrlActionNode(IUrlActionNode node);
    static void unRegisterUrlActionNodes(const QVector<IUrlActionNode>& functionNodes);
    static bool containUrlPath(const QString& url, IHttpMethod method);

    static void registerStaticFiles(const QString& path, const QString& prefix);

    static void registerPathValidator(const QString& name, const QString& regexp="/");
    static void registerPathValidator(const QString& name, ValidatorFun fun);

    // TODO: 这里需要考虑添加到 global 和 local 的两种情形，之后添加上来，作为 AOP 的一部分。
    static void registerPreProcessor(IProcessorWare* middleWare);
    static void registerPostProcessor(IProcessorWare* middleWare);
    static void registerPreInterceptor(IInterceptorWare* middleWare);
    static void registerPostInterceptor(IInterceptorWare* middleWare);

    static void travalPrintUrlTree();
    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

    static IUrlActionNode* getUrlActionNode(IRequest& request);
    static IUrlActionNode* getUrlActionNode(const QString& path, IHttpMethod method);
    static IStatusActionNode* getStatusActionNode(IHttpStatus status);
    static QString getStaticFileActionPath(const IRequest& request);

    static void setDefaultStaticDir(const QString& prefix);
    static QString getDefaultStaticDir();

    static bool preIntercept(IRequest& request, IResponse& response);
    static bool postIntercept(IRequest& request, IResponse& response);
    static bool preProcess(IRequest& request, IResponse& response);
    static bool postProcess(IRequest& request, IResponse& response);

private:
    static QVector<IUrlActionNode*> queryFunctionNodes(IControllerRouteNode* parentNode, const QStringList& fragments, IHttpMethod method);
    static QMap<QString, QByteArray> getPathVariable(void* node, const QStringList& fragments);

    // 这里实现 url 时 需要防止  /<name>/<name>/  这种重复类型的 url
    static bool checkUrlDuplicateName(const IUrlActionNode* node);
    void preRegisterPathValidator();

    static void checkRegisterAvalible();    // 检查是否能够注册

private:
    bool m_isServerStarted{false};
    std::shared_ptr<IControllerRouteNode> m_urlMapppings;
    std::shared_ptr<IControllerFileNode> m_fileMappings;

    QString m_staticFilePrefix {};      // static served file dir;

    QMap<IHttpStatus, IStatusActionNode> m_statusMappings;
    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;

    QVector<IProcessorWare*> m_preProcessors;
    QVector<IProcessorWare*> m_postProcessors;

    QVector<IInterceptorWare*> m_preInterceptors;
    QVector<IInterceptorWare*> m_postInterceptors;
};

$PackageWebCoreEnd
