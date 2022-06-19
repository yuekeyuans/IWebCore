#pragma once
#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMethod.h"

$PackageWebCoreBegin

struct IUrlFunctionNode;

class IControllerRouteNode
{
private:
    using ValidateFun = bool (*)(const QString&);

public:
    enum NodeType{
        TEXT_MATCH,
        REGEXP_MATCH,
        FUNC_MATCH,
        FULL_MATCH
    };

public:
    IControllerRouteNode() = default;
    explicit IControllerRouteNode(IControllerRouteNode* parent, const QString& nodeName);

    IUrlFunctionNode* setLeaf(const IUrlFunctionNode& leaf);
    IUrlFunctionNode* getLeaf(IHttpMethod method);
    IUrlFunctionNode* removeLeaf(IHttpMethod method);

    void addChildNode(const IControllerRouteNode& node);
    QVector<IControllerRouteNode*> getChildNodes(const QString nodeName);
    QVector<IControllerRouteNode*> getParentNodes();
    IControllerRouteNode* getOrAppendChildNode(const QString& nodeName);
    IControllerRouteNode* getChildNode(const QString& nodeName);

    void travelPrint(int space=0) const;

private:
    bool contains(const QString& nodeName);
    void evaluateNode(const QString& nodeName);
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
    IUrlFunctionNode *getMethodLeaf{nullptr};
    IUrlFunctionNode *putMethodLeaf{nullptr};
    IUrlFunctionNode *postMethodLeaf{nullptr};
    IUrlFunctionNode *deleteMethodLeaf{nullptr};
    IUrlFunctionNode *patchMethodLeaf{nullptr};
    IControllerRouteNode* parentNode{nullptr};
};

$PackageWebCoreEnd
