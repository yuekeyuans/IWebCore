#pragma once
#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMethod.h"

$PackageWebCoreBegin

struct IUrlActionNode;

class IControllerRouteNode
{
private:
    using ValidateFun = bool (*)(const QString&);
    using IUrlActionNodeStar = IUrlActionNode*;

public:
    enum NodeType{
        TEXT_MATCH,
        REGEXP_MATCH,
        FUNC_MATCH,
        FULL_MATCH
    };

public:
    IControllerRouteNode() = default;
    explicit IControllerRouteNode(IControllerRouteNode* parent, const QString& fragment);

    bool isEmpty();
    IUrlActionNode* setLeaf(const IUrlActionNode& leaf);
    IUrlActionNode* getLeaf(IHttpMethod method);
    void removeLeaf(IHttpMethod method);

    void addChildNode(const IControllerRouteNode& node);
    void removeChildNode(const IControllerRouteNode& node);

    QVector<IControllerRouteNode*> getChildNodes(const QString nodeName);
    QVector<IControllerRouteNode*> getParentNodes();
    IControllerRouteNode* getOrAppendChildNode(const QString& fragment);
    IControllerRouteNode* getChildNode(const QString& fragment);

    void travelPrint(int space=0) const;

    bool operator==(const IControllerRouteNode& node);

private:
    IUrlActionNodeStar& getLeafRef(IHttpMethod method);
    bool containFragment(const QString& fragment);
    void evaluateNode(const QString& fragment);
    bool evaluatePlainText(const QString& nodeName);
    bool evaluateTypeEmptyNode(const QString& nodeName);
    bool evaluateNameOnlyNode(const QString& nodeName);
    bool evaluateNameTypeNode(const QString& nodeName);
    bool evaluateRegTypeNode(const QString& nodeName);
    bool evaluateUnMatchedNode(const QString& nodeName);

public:
    NodeType type;
    QString name;
    QString fragment;
    QRegularExpression regexpValidator;     // 使用 正则式验证数据的正确性与否
    ValidateFun funValidator;               // 使用 函数 验证数据是否正确

    QList<IControllerRouteNode> children;

    IUrlActionNode *getMethodLeaf{nullptr};
    IUrlActionNode *putMethodLeaf{nullptr};
    IUrlActionNode *postMethodLeaf{nullptr};
    IUrlActionNode *deleteMethodLeaf{nullptr};
    IUrlActionNode *patchMethodLeaf{nullptr};
    IControllerRouteNode* parentNode{nullptr};
};

$PackageWebCoreEnd
