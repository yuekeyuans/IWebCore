#include "IJarUnit.h"
#include "core/base/IConstantUtil.h"

$PackageWebCoreBegin

IJarUnit::IJarUnit(IReqRespRaw* raw){
    m_raw = raw;
}

bool IJarUnit::isValid() const
{
    return m_raw != nullptr;
}

$PackageWebCoreEnd
