#pragma once

#include "core/util/IPackageUtil.h"
#include "core/base/IStringView.h"

$PackageWebCoreBegin

class IStringViewStash
{
public:
    IStringViewStash() = default;

public:
    IStringView stash(const char* data);
    IStringView stash(const QByteArray& data);
    IStringView stash(const QString& data);
    IStringView stash(const std::string& data);

private:
    QMutex m_mutex;
    std::list<QByteArray> m_stashed;
};

class IGlobalStringViewStash
{
    IGlobalStringViewStash() = delete;
    IGlobalStringViewStash(const char* data);
    IGlobalStringViewStash(const QByteArray& data);
    IGlobalStringViewStash(const QString& data);
    IGlobalStringViewStash(const std::string& data);
    operator IStringView() const;

public:
    IStringView view() const;

private:
    IStringView m_view;
    static IStringViewStash m_stash;
};

$PackageWebCoreEnd
