#include "IResponseManage.h"
#include "IResponseWareRaw.h"
#include "IResponseWare.h"

$PackageWebCoreBegin

void IResponseManage::registerResponseType(IResponseWare *response)
{
    m_responses.append(response);
    if(!response->getPrefixMatcher().isEmpty()){
        if(stringConvertResponses.contains(response->getPrefixMatcher())){
            QString tip = QString("already contain response prefix matcher. name : ").append(response->getPrefixMatcher());
            qFatal(tip.toUtf8());
        }
        stringConvertResponses[response->getPrefixMatcher()] = response;
    }
}

IResponseWare* IResponseManage::convertMatch(const QString &content)
{
    static QStringList keys = stringConvertResponses.keys();
    for(const auto& key : keys){
        if(content.startsWith(key)){
            return stringConvertResponses[key];
        }

    }

    return nullptr;
}

$PackageWebCoreEnd
