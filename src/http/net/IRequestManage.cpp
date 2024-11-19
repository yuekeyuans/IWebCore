#include "IRequestManage.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

void IRequestManage::pushRequest(IRequest *request)
{
    m_requests.emplace(request);
}

void IRequestManage::popRequest(IRequest *request)
{
    m_requests.erase(request);
    delete request;
}

$PackageWebCoreEnd
