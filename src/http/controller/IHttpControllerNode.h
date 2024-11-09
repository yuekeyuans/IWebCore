#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IHttpUrlFragment.h"

$PackageWebCoreBegin

struct IHttpControllerAction;
class IHttpControllerNode
{
private:
    using IHttpControllerActionPtr = IHttpControllerAction*;

public:
    IHttpControllerNode() = default;
    explicit IHttpControllerNode(IHttpControllerNode* parent, const IHttpUrlFragment& fragment);
    bool operator==(const IHttpControllerNode& node);

public:
    bool isEmpty() const;
    IHttpControllerAction* setLeaf(const IHttpControllerAction& leaf);
    IHttpControllerAction* getLeaf(IHttpMethod method);

    void addChildNode(const IHttpControllerNode& node);
    void removeChildNode(const IHttpControllerNode& node);

    QVector<IHttpControllerNode*> getChildNodes(IStringView nodeName);
    QVector<IHttpControllerNode*> getParentNodes();
    IHttpControllerNode* getOrAppendChildNode(const IHttpUrlFragment& fragment);
    IHttpControllerNode* getChildNode(const QString& fragment);

    void travelPrint(int space=0) const;

private:
    bool containFragment(const QString& fragment);

public:
    IHttpUrlFragment routeNode;
    IHttpControllerNode* parentNode{nullptr};
    IHttpControllerAction *getMethodLeaf{nullptr};
    IHttpControllerAction *putMethodLeaf{nullptr};
    IHttpControllerAction *postMethodLeaf{nullptr};
    IHttpControllerAction *deleteMethodLeaf{nullptr};
    IHttpControllerAction *patchMethodLeaf{nullptr};
    QList<IHttpControllerNode> children;
};

$PackageWebCoreEnd
