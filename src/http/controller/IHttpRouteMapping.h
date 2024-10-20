#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

struct IHttpControllerActionNode;

class IHttpRouteMapping
{
private:
    using IUrlActionNodePtr = IHttpControllerActionNode*;

public:
    IHttpRouteMapping() = default;
    explicit IHttpRouteMapping(IHttpRouteMapping* parent, const QString& fragment);
    bool operator==(const IHttpRouteMapping& node);

public:
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

private:
    IUrlActionNodePtr& getLeafRef(IHttpMethod method);
    bool containFragment(const QString& fragment);

public:
    IUrlFragmentNode routeNode;
    IHttpRouteMapping* parentNode{nullptr};
    IHttpControllerActionNode *getMethodLeaf{nullptr};
    IHttpControllerActionNode *putMethodLeaf{nullptr};
    IHttpControllerActionNode *postMethodLeaf{nullptr};
    IHttpControllerActionNode *deleteMethodLeaf{nullptr};
    IHttpControllerActionNode *patchMethodLeaf{nullptr};
    QList<IHttpRouteMapping> children;
};

$PackageWebCoreEnd
