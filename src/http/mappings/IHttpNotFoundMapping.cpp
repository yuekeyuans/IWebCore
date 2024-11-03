#include "IHttpNotFoundMapping.h"

$PackageWebCoreBegin

void IHttpNotFoundMapping::travelPrint() const
{
    qDebug() << "NotFound Mapping:" << $order();
    qDebug().noquote() << "  " << $name();
}

IHttpAction *IHttpNotFoundMapping::getAction(IRequest &request) const
{
    Q_UNUSED(request)
    return const_cast<IHttpNotFoundAction*>(&m_action);
}

double IHttpNotFoundMapping::$order() const
{
    return 100.0;
}

$PackageWebCoreEnd
