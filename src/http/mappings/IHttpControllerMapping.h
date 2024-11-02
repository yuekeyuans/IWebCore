// TODO: 之后文件夹应该被重构
#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/mappings/IHttpMappingInterface.h"
#include "http/controller/detail/IHttpRouteNode.h"

$PackageWebCoreBegin

class IHttpControllerMapping : public IHttpMappingInterface<IHttpControllerMapping>
{
public:
    IHttpControllerMapping() = default;

public:
    void registerUrlActionNode(IHttpControllerAction node);
    void registerUrlActionNodes(const QVector<IHttpControllerAction>& functionNodes);

public:
    virtual void travelPrint() final;
    virtual std::vector<IHttpAction*> getActions(IRequest &request);

private:
    bool checkUrlDuplicateName(const IHttpControllerAction* node);
    void checkRegisterAvalible();    // 检查是否能够注册
    std::vector<IHttpAction*> queryFunctionNodes(IHttpRouteNode* parentNode, const IStringViewList& fragments, IHttpMethod method);
    QMap<IStringView, IStringView> getPathVariable(void* node, const IStringViewList& fragments);



private:
    IHttpRouteNode m_urlMapppings;

};

$PackageWebCoreEnd
