#pragma once

#include "core/util/IPackageUtil.h"
#include "core/base/IStringView.h"
#include "core/base/IStringData.h"

$PackageWebCoreBegin

class IStringViewStash
{
public:
    IStringViewStash() = default;

public:
    IStringView stash(const char* data);
    IStringView stash(QByteArray&& data);
    IStringView stash(const QByteArray& data);
    IStringView stash(const QString& data);
    IStringView stash(std::string&& data);
    IStringView stash(const std::string& data);

private:
    std::list<IStringData> m_stashed;
};

$PackageWebCoreEnd
