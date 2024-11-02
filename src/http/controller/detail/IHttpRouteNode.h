#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

struct IHttpControllerAction;

class IHttpRouteNode
{
private:
    using IUrlActionNodePtr = IHttpControllerAction*;

public:
    IHttpRouteNode() = default;
    explicit IHttpRouteNode(IHttpRouteNode* parent, const QString& fragment);
    bool operator==(const IHttpRouteNode& node);

public:
    bool isEmpty() const;
    IHttpControllerAction* setLeaf(const IHttpControllerAction& leaf);
    IHttpControllerAction* getLeaf(IHttpMethod method);
    void removeLeaf(IHttpMethod method);

    void addChildNode(const IHttpRouteNode& node);
    void removeChildNode(const IHttpRouteNode& node);

    QVector<IHttpRouteNode*> getChildNodes(IStringView nodeName);
    QVector<IHttpRouteNode*> getParentNodes();
    IHttpRouteNode* getOrAppendChildNode(const QString& fragment);
    IHttpRouteNode* getChildNode(const QString& fragment);

    void travelPrint(int space=0) const;

private:
    IUrlActionNodePtr& getLeafRef(IHttpMethod method);
    bool containFragment(const QString& fragment);

public:
    IUrlFragmentNode routeNode;
    IHttpRouteNode* parentNode{nullptr};
    IHttpControllerAction *getMethodLeaf{nullptr};
    IHttpControllerAction *putMethodLeaf{nullptr};
    IHttpControllerAction *postMethodLeaf{nullptr};
    IHttpControllerAction *deleteMethodLeaf{nullptr};
    IHttpControllerAction *patchMethodLeaf{nullptr};
    QList<IHttpRouteNode> children;
};

$PackageWebCoreEnd
