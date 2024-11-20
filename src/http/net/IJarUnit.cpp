#include "IJarUnit.h"
#include "core/util/IConstantUtil.h"
#include "http/net/impl/IRequestImpl.h"


$PackageWebCoreBegin

IJarUnit::IJarUnit() : m_raw(*static_cast<IRequestImpl*>(nullptr))
{
        IGlobalAbort::abortUnVisibleMethod();
}

IJarUnit::IJarUnit(IRequestImpl& raw)
    : m_raw(raw)
{
}

//bool IJarUnit::isValid() const
//{
//    return m_raw != nullptr;
//}

$PackageWebCoreEnd
