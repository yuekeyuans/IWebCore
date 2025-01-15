#include "IResponseManage.h"
#include "core/util/IStringUtil.h"
#include "IResponseWare.h"
#include "IResponseTemplateRenderer.h"
#include "http/detail/IResponseRaw.h"

$PackageWebCoreBegin

void IResponseManage::registerResponse(const std::string& name, IResponseWare *response)
{
    assert(!m_responses.contains(name));
    m_responses[name] = response;

    if(!response->prefixMatcher().empty()){
        assert(!m_convertableResponses.contains(response->prefixMatcher()));
        m_convertableResponses[response->prefixMatcher()] = response;
    }
}

bool IResponseManage::containResponse(const std::string &name)
{
    const auto& keys = m_responses.keys();
    for(const auto& key : keys){
        if(IStringUtil::endsWith(key, name)){
            return true;
        }
    }
    return false;
}

IResponseWare* IResponseManage::convertableMatch(const std::string &content)
{
    for(auto it=m_convertableResponses.begin(); it!= m_convertableResponses.end(); it++){
        if(IStringUtil::startsWith(content, it.key())){
            return it.value();
        }
    }

    return nullptr;
}

$PackageWebCoreEnd
