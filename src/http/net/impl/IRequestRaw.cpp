#include "IRequestRaw.h"
#include "core/util/IHeaderUtil.h"
#include "core/util/IConstantUtil.h"
//#include "core/util/IToeUtil.h"
//#include "core/util/IXmlUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/ICookieJar.h"
#include "http/net/IHeaderJar.h"
#include "http/net/ISessionJar.h"
#include "http/net/IMultiPartJar.h"
#include "http/net/impl/IResponseRaw.h"
#include "http/session/ISessionManager.h"

$PackageWebCoreBegin

IRequestRaw::IRequestRaw()
    : m_request(*static_cast<IRequest*>(nullptr))
{
    IGlobalAbort::abortUnVisibleMethod();
}

IRequestRaw::IRequestRaw(IRequest& request)
    : m_request(request)
{
    m_headerJar = new IHeaderJar(this);
    m_cookieJar = new ICookieJar(this);
    m_multiPartJar = new IMultiPartJar(this);
    m_responseRaw = new IResponseRaw;

    if(ISessionManager::instance()->getSessionWare() != nullptr){
        m_sessionJar = new ISessionJar(this);
    }
}

IRequestRaw::~IRequestRaw()
{
    delete m_headerJar;
    delete m_cookieJar;
    delete m_multiPartJar;
    delete m_sessionJar;
    delete m_responseRaw;
}

bool IRequestRaw::isValid() const
{
    return m_responseRaw->isValid();
}

void IRequestRaw::setInvalid(IHttpInvalidWare ware)
{
    m_responseRaw->setMime(IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8));
    m_responseRaw->status = ware.status;
    m_responseRaw->setContent(std::move(ware));
}


$PackageWebCoreEnd
