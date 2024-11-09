#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/mappings/IHttpMappingInterface.h"
#include "http/controller/IHttpControllerNode.h"

$PackageWebCoreBegin

class IHttpControllerMapping : public IHttpMappingInterface<IHttpControllerMapping>
{
public:
    IHttpControllerMapping() = default;

public:
    void registerUrlActionNode(const IHttpControllerAction& node);

public:
    virtual void travelPrint() const final;
    virtual IHttpAction* getAction(IRequest &request) const;

private:
    std::vector<IHttpAction*> queryFunctionNodes(IHttpControllerNode* parentNode, const IStringViewList& fragments, IHttpMethod method) const;

private:
    IHttpControllerNode m_urlMapppings;

};

$PackageWebCoreEnd
