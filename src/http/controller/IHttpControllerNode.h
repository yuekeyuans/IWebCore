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
    explicit IHttpControllerNode(const IHttpUrlFragment& fragment);
    bool operator==(const IHttpControllerNode& node);

public:
    bool isEmpty() const;

    void setAction(const IHttpControllerAction& action);
    IHttpControllerAction* getAction(IHttpMethod method) const;

    void addChild(const IHttpUrlFragment& fragment);
    void addChild(const IHttpControllerNode& node);
    IHttpControllerNode* getChild(const IHttpUrlFragment& fragment);

    QVector<const IHttpControllerNode*> getChildren(IStringView nodeName) const;
    void travelPrint(int space=0) const;

public:
    IHttpUrlFragment urlFragment;
    IHttpControllerAction *getMethodAction{nullptr};
    IHttpControllerAction *putMethodAction{nullptr};
    IHttpControllerAction *postMethodAction{nullptr};
    IHttpControllerAction *deleteMethodAction{nullptr};
    IHttpControllerAction *patchMethodAction{nullptr};
    QList<IHttpControllerNode> children;
};

$PackageWebCoreEnd
