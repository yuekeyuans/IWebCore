﻿#include "IJarUnit.h"
#include "core/util/IConstantUtil.h"

$PackageWebCoreBegin

IJarUnit::IJarUnit(IRequestRaw* raw){
    m_raw = raw;
}

bool IJarUnit::isValid() const
{
    return m_raw != nullptr;
}

$PackageWebCoreEnd
