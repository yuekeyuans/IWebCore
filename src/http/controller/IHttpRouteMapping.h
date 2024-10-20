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
    enum NodeType{
        TEXT_MATCH,
        REGEXP_MATCH,
        FUNC_MATCH,
        FULL_MATCH
    };

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
    void evaluateNode(const QString& fragment);
    bool evaluatePlainText(const QString& nodeName);
    bool evaluateTypeEmptyNode(const QString& nodeName);
    bool evaluateNameOnlyNode(const QString& nodeName);
    bool evaluateNameTypeNode(const QString& nodeName);
    bool evaluateRegTypeNode(const QString& nodeName);
    bool evaluateUnMatchedNode(const QString& nodeName);

public:
//    NodeType type;
//    QString name;
//    QString fragment;
//    QRegularExpression regexpValidator;     // 使用 正则式验证数据的正确性与否
//    ValidateFun funValidator;               // 使用 函数 验证数据是否正确

    IHttpRouteNote routeNode;       // TODO: 上面的五项替换成这个 routeNode

    QList<IHttpRouteMapping> children;

    IHttpControllerActionNode *getMethodLeaf{nullptr};
    IHttpControllerActionNode *putMethodLeaf{nullptr};
    IHttpControllerActionNode *postMethodLeaf{nullptr};
    IHttpControllerActionNode *deleteMethodLeaf{nullptr};
    IHttpControllerActionNode *patchMethodLeaf{nullptr};
    IHttpRouteMapping* parentNode{nullptr};
};

$PackageWebCoreEnd
