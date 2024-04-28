#include "IHttpInvalidManage.h"

void IWebCore::IHttpInvalidManage::addWare(IWebCore::IHttpInvalidWare *ware)
{
    auto name = ware->tag;
    m_wares[name] = ware;
}

IWebCore::IHttpInvalidWare *IWebCore::IHttpInvalidManage::getWare(const QString &name)
{
    if(m_wares.contains(name)){
        return nullptr;
    }
    return m_wares[name];
}
