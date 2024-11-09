#pragma once
#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpMethod.h"
#include "http/controller/detail/IHttpUrlFragment.h"

$PackageWebCoreBegin

struct IHttpControllerAction;
class IHttpControllerNode
{
public:
    IHttpControllerNode() = default;
    explicit IHttpControllerNode(IHttpControllerNode* parent, const IHttpUrlFragment& fragment);
    bool operator==(const IHttpControllerNode& node);

public:
    bool isEmpty() const;

    void setLeaf(const IHttpControllerAction& leaf);
    IHttpControllerAction* getLeaf(IHttpMethod method);

    void addChildNode(const IHttpUrlFragment& fragment);
    void addChildNode(const IHttpControllerNode& node);
    IHttpControllerNode* getChildNode(const IHttpUrlFragment& fragment);

    QVector<IHttpControllerNode*> getChildNodes(IStringView nodeName);
    void travelPrint(int space=0) const;

public:
    IHttpUrlFragment urlFragment;
    IHttpControllerAction *getMethodLeaf{nullptr};
    IHttpControllerAction *putMethodLeaf{nullptr};
    IHttpControllerAction *postMethodLeaf{nullptr};
    IHttpControllerAction *deleteMethodLeaf{nullptr};
    IHttpControllerAction *patchMethodLeaf{nullptr};
    QList<IHttpControllerNode> children;
};

$PackageWebCoreEnd
