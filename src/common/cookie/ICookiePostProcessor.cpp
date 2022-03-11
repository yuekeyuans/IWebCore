#include "ICookiePostProcessor.h"
#include "common/net/IRequest.h"
#include "common/net/impl/IReqRespRaw.h"

$PackageWebCoreBegin

bool ICookiePostProcessor::match(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)

    return true;
}

bool ICookiePostProcessor::action(IRequest &request, IResponse &response)
{
    Q_UNUSED(response)
    auto raw = request.getRaw();
    if(!raw->m_responseCookies.isEmpty()){
        raw->m_responseHeaders["Set-Cookie"] = "abc=123";
    }
    return true;
}

$PackageWebCoreEnd
