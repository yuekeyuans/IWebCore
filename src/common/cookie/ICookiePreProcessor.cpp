#include "ICookiePreProcessor.h"

#include "common/net/IRequest.h"

$PackageWebCoreBegin

bool ICookiePreProcessor::match(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)

    return true;
}

bool ICookiePreProcessor::action(IRequest &request, IResponse &response)
{
    Q_UNUSED(response)

    bool ok;
    auto value = request.getHeaderParameter("Cookie", &ok);
    if(ok){
        auto parts = value.split(';');
        qDebug() << parts;
    }

    return true;
}

$PackageWebCoreEnd
