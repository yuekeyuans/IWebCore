#include "IResponseManage.h"
#include "IResponseWareRaw.h"
#include "IResponseWare.h"

$PackageWebCoreBegin

void IResponseManage::registerResponseType(IResponseWare *response)
{
    instance()->responses.append(response);
    if(response->canConvertFromString()){
        instance()->stringConvertResponses.append(response);
    }
}

IResponseWare* IResponseManage::convertMatch(const QString &content)
{
    for(auto response : instance()->stringConvertResponses){
        if(response->matchConvertString(content)){
            return response;
        }
    }
    return nullptr;
}

$PackageWebCoreEnd
