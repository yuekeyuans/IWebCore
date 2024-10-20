#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IHttpRouteLeafNode.h"

#include "IHttpRouteInnerNode.h"
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

    void registerUrlActionNode(IHttpRouteLeafNode node);
    void registerUrlActionNodes(const QVector<IHttpRouteLeafNode>& functionNodes);

    void registerStaticFiles(const QString& path, const QString& prefix);

    void registerPathValidator(const QString& name, const QString& regexp);
    void registerPathValidator(const QString& name, ValidatorFun fun);

    static void travalPrintUrlTree();
    static QString queryPathRegValidator(const QString& path);
    static ValidatorFun queryPathFunValidator(const QString& path);

    bool isUrlActionNodeEnabled() const;
    IHttpRouteLeafNode* getUrlActionNode(IRequest& request);

    bool isStaticFileActionPathEnabled();
    QString getStaticFileActionPath(const IRequest& request);
    QStringList getStaticFolderActionPath(const IRequest& request);

private:
    static QVector<IHttpRouteLeafNode*> queryFunctionNodes(IHttpRouteInnerNode* parentNode, const IStringViewList& fragments, IHttpMethod method);
    static QMap<IStringView, IStringView> getPathVariable(void* node, const IStringViewList& fragments);

    // 这里实现 url 时 需要防止  /<name>/<name>/  这种重复类型的 url
    static bool checkUrlDuplicateName(const IHttpRouteLeafNode* node);
    static void checkRegisterAvalible();    // 检查是否能够注册

private:
    bool m_isServerStarted{false};
    IHttpRouteInnerNode m_urlMapppings;
    IHttpResourceMapping m_resourceMappings;
    IHttpFolderMapping m_folderMappings;

    QMap<QString, QString> m_pathRegValidators;
    QMap<QString, ValidatorFun> m_pathFunValidators;
};

$PackageWebCoreEnd
