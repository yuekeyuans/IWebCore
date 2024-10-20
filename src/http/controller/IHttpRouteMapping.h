#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IHttpRouteNode.h"

$PackageWebCoreBegin

struct IHttpControllerActionNode;

class IHttpRouteMapping
{
private:
    using ValidateFun = std::function<bool(const QString&)>;
    using IUrlActionNodePtr = IHttpControllerActionNode*;

public:
    IHttpRouteMapping() = default;
    explicit IHttpRouteMapping(IHttpRouteMapping* parent, const QString& fragment);

    bool isEmpty() const;
    IHttpControllerActionNode* setLeaf(const IHttpControllerActionNode& leaf);
    IHttpControllerActionNode* getLeaf(IHttpMethod method);
    void removeLeaf(IHttpMethod method);

    void addChildNode(const IHttpRouteMapping& node);
    void removeChildNode(const IHttpRouteMapping& node);

    QVector<IHttpRouteMapping*> getChildNodes(IStringView nodeName);
    QVector<IHttpRouteMapping*> getParentNodes();
    IHttpRouteMapping* getOrAppendChildNode(const QString& fragment);
    IHttpRouteMapping* getChildNode(const QString& fragment);

    void travelPrint(int space=0) const;

    bool operator==(const IHttpRouteMapping& node);

private:
    IUrlActionNodePtr& getLeafRef(IHttpMethod method);
    bool containFragment(const QString& fragment);

public:
    IHttpRouteNode routeNode;
    IHttpRouteMapping* parentNode{nullptr};
    IHttpControllerActionNode *getMethodLeaf{nullptr};
    IHttpControllerActionNode *putMethodLeaf{nullptr};
    IHttpControllerActionNode *postMethodLeaf{nullptr};
    IHttpControllerActionNode *deleteMethodLeaf{nullptr};
    IHttpControllerActionNode *patchMethodLeaf{nullptr};
    QList<IHttpRouteMapping> children;
};

$PackageWebCoreEnd
