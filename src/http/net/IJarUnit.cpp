#include "IJarUnit.h"
#include "core/util/IConstantUtil.h"
#include "core/abort/IGlobalAbort.h"
#include "http/net/impl/IRequestImpl.h"
#include "http/net/IRequest.h"

$PackageWebCoreBegin

IJarUnit::IJarUnit() : m_raw(*static_cast<IRequestImpl*>(nullptr))
{
    IGlobalAbort::abortUnVisibleMethod();
}

IJarUnit::IJarUnit(IRequestImpl& raw) : m_raw(raw)
{
}

IJarUnit::IJarUnit(IRequest & request) : m_raw(request.getImpl())
{
}

$PackageWebCoreEnd
