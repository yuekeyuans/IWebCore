// TODO: 之后文件夹应该被重构
#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/IHttpMappingInterface.h"
#include "http/controller/detail/IHttpRouteNode.h"

$PackageWebCoreBegin

class IHttpRouteMapping : public IHttpMappingInterface<IHttpRouteMapping>
{
public:
    IHttpRouteMapping() = default;

public:
    void registerUrlActionNode(IHttpAction node);
    void registerUrlActionNodes(const QVector<IHttpAction>& functionNodes);

public:
    virtual void travelPrint() final;
    virtual IHttpAction* getUrlActionNode(IRequest &request);

private:
    bool checkUrlDuplicateName(const IHttpAction* node);
    void checkRegisterAvalible();    // 检查是否能够注册
    QVector<IHttpAction*> queryFunctionNodes(IHttpRouteNode* parentNode, const IStringViewList& fragments, IHttpMethod method);
    QMap<IStringView, IStringView> getPathVariable(void* node, const IStringViewList& fragments);



private:
    IHttpRouteNode m_urlMapppings;

};

$PackageWebCoreEnd
