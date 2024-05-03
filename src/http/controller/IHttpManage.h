#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IPreProcessorUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/middleware/IMiddleWare.h"
#include "http/middleware/IInterceptorWare.h"
#include "http/middleware/IProcessorWare.h"
#include "http/node/IUrlActionNode.h"
//#include "http/node/IStatusActionNode.h"

#include "IHttpRouteMapping.h"
#include "IHttpResourceMapping.h"
#include "IHttpFolderMapping.h"

$PackageWebCoreBegin

class IRequest;
class IHttpManage : public ISingletonUnit<IHttpManage>
{
    using ValidatorFun = std::function<bool(const QString&)>;
public:
    IHttpManage() = default;

public:
    static void setIsServerStarted(bool);

    void registerUrlActionNode(IUrlActionNode node);
    void registerUrlActionNodes(const QVector<IUrlActionNode>& functionNodes);

    void registerStaticFiles(const QString& path, const QString& prefix);

    void registerPathValidator(const QString& name, const QString& regexp);
    void registerPathValidator(const QString& name, ValidatorFun fun);

    static void registerPreProcessor(IProcessorWare* middleWare);
    static void registerPostProcessor(IProcessorWare* middleWare);
    static void registerPreInterceptor(IInterceptorWare* middleWare);
    static void registerPostInterceptor(IInterceptorWare* middleWare);

    static void travalPrintUrlTree();
    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

    bool isUrlActionNodeEnabled() const;
    IUrlActionNode* getUrlActionNode(IRequest& request);

    bool isStaticFileActionPathEnabled();
    QString getStaticFileActionPath(const IRequest& request);
    QStringList getStaticFolderActionPath(const IRequest& request);

//    static bool preIntercept(IRequest& request, IResponse& response);
//    static bool postIntercept(IRequest& request, IResponse& response);
//    static bool preProcess(IRequest& request, IResponse& response);
//    static bool postProcess(IRequest& request, IResponse& response);

private:
    static QVector<IUrlActionNode*> queryFunctionNodes(IHttpRouteMapping* parentNode, const QStringList& fragments, IHttpMethod method);
    static QMap<QString, QByteArray> getPathVariable(void* node, const QStringList& fragments);

    // 这里实现 url 时 需要防止  /<name>/<name>/  这种重复类型的 url
    static bool checkUrlDuplicateName(const IUrlActionNode* node);

    static void checkRegisterAvalible();    // 检查是否能够注册

private:
    bool m_isServerStarted{false};
    IHttpRouteMapping m_urlMapppings;
    IHttpResourceMapping m_resourceMappings;
    IHttpFolderMapping m_folderMappings;

    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;

//    QVector<IProcessorWare*> m_preProcessors;
//    QVector<IProcessorWare*> m_postProcessors;

//    QVector<IInterceptorWare*> m_preInterceptors;
//    QVector<IInterceptorWare*> m_postInterceptors;
};

$PackageWebCoreEnd
