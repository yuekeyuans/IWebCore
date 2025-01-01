#include "IHttpPathFragment.h"
#include "http/IHttpManage.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

bool IHttpPathFragment::isMatch(IStringView value) const
{
    return isMatch(value.toQString());
}

bool IHttpPathFragment::isMatch(const QString &nodeName) const
{
    return false
            || type == IHttpPathFragment::TEXT_MATCH && fragment == nodeName
            || type == IHttpPathFragment::REGEXP_MATCH && regexpValidator.match(nodeName).hasMatch()
            || type == IHttpPathFragment::FUNC_MATCH && funValidator(nodeName)
            || type == IHttpPathFragment::FULL_MATCH;
}

$PackageWebCoreEnd




