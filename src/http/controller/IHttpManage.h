#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/node/IUrlActionNode.h"

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

    static void travalPrintUrlTree();
    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

    bool isUrlActionNodeEnabled() const;
    IUrlActionNode* getUrlActionNode(IRequest& request);

    bool isStaticFileActionPathEnabled();
    QString getStaticFileActionPath(const IRequest& request);
    QStringList getStaticFolderActionPath(const IRequest& request);

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
};

$PackageWebCoreEnd
