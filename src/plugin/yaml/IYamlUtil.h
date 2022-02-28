#pragma once

#include "base/IHeaderUtil.h"

$PackageWebCoreBegin

/**
 * 在可 预见的未来， Yaml 只有使用在 configuration 当中，所以 这里不把这个类放置在 base 里面。
 */
namespace IYamlUtil
{
    QJsonObject toJsonObject(const QString& content, bool* ok);
};


$PackageWebCoreEnd
