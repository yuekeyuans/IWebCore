#include "IRequestRaw.h"
#include "core/util/IHeaderUtil.h"
#include "core/util/IConstantUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/invalid/IHttpBadRequestInvalid.h"
#include "http/net/ICookieJar.h"
#include "http/net/IHeaderJar.h"
#include "http/net/ISessionJar.h"
#include "http/net/IMultiPartJar.h"
#include "http/net/IRequest.h"
#include "http/net/impl/IRequestImpl.h"
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
    m_headerJar = new IHeaderJar(request);
    m_cookieJar = new ICookieJar(request);
    m_multiPartJar = new IMultiPartJar(request);

    if(ISessionManager::instance()->getSessionWare() != nullptr){
        m_sessionJar = new ISessionJar(request);
    }
}

IRequestRaw::~IRequestRaw()
{
    delete m_headerJar;
    delete m_cookieJar;
    delete m_multiPartJar;
    delete m_sessionJar;
}

bool IRequestRaw::isValid() const
{
    return m_request.getImpl().m_respRaw.isValid();
}

void IRequestRaw::setInvalid(IHttpInvalidWare ware)
{
    auto& respRaw = m_request.getImpl().m_respRaw;
    respRaw.setMime(IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8));
    respRaw.status = ware.status;
    respRaw.setContent(std::move(ware));
}

$PackageWebCoreEnd
