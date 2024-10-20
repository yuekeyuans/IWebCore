#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IUrlFragmentNode.h"

$PackageWebCoreBegin

struct IHttpRouteLeafNode;

class IHttpRouteInnerNode
{
private:
    using IUrlActionNodePtr = IHttpRouteLeafNode*;

public:
    IHttpRouteInnerNode() = default;
    explicit IHttpRouteInnerNode(IHttpRouteInnerNode* parent, const QString& fragment);
    bool operator==(const IHttpRouteInnerNode& node);

public:
    bool isEmpty() const;
    IHttpRouteLeafNode* setLeaf(const IHttpRouteLeafNode& leaf);
    IHttpRouteLeafNode* getLeaf(IHttpMethod method);
    void removeLeaf(IHttpMethod method);

    void addChildNode(const IHttpRouteInnerNode& node);
    void removeChildNode(const IHttpRouteInnerNode& node);

    QVector<IHttpRouteInnerNode*> getChildNodes(IStringView nodeName);
    QVector<IHttpRouteInnerNode*> getParentNodes();
    IHttpRouteInnerNode* getOrAppendChildNode(const QString& fragment);
    IHttpRouteInnerNode* getChildNode(const QString& fragment);

    void travelPrint(int space=0) const;

private:
    IUrlActionNodePtr& getLeafRef(IHttpMethod method);
    bool containFragment(const QString& fragment);

public:
    IUrlFragmentNode routeNode;
    IHttpRouteInnerNode* parentNode{nullptr};
    IHttpRouteLeafNode *getMethodLeaf{nullptr};
    IHttpRouteLeafNode *putMethodLeaf{nullptr};
    IHttpRouteLeafNode *postMethodLeaf{nullptr};
    IHttpRouteLeafNode *deleteMethodLeaf{nullptr};
    IHttpRouteLeafNode *patchMethodLeaf{nullptr};
    QList<IHttpRouteInnerNode> children;
};

$PackageWebCoreEnd
