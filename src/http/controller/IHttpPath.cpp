﻿#include "IHttpPath.h"

$PackageWebCoreBegin

bool IHttpPathFragment::isMatch(IStringView value) const
{
    return isMatch(value.toQString());
}

bool IHttpPathFragment::isMatch(const QString &nodeName) const
{
    return false
            || m_type == IHttpPathFragment::TEXT_MATCH && m_fragment == nodeName
            || m_type == IHttpPathFragment::FUNC_MATCH && m_validator(nodeName)
            || m_type == IHttpPathFragment::FULL_MATCH;
}

$PackageWebCoreEnd