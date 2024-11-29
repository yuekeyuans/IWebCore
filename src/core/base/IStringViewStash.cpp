#include "IStringViewStash.h"

$PackageWebCoreBegin

IStringView IStringViewStash::stash(const char *data)
{
    return stash(QByteArray(data));
}

IStringView IStringViewStash::stash(QByteArray &&data)
{
    m_stashed.emplace_back(std::move(data));
    return m_stashed.back();
}

IStringView IStringViewStash::stash(const QByteArray &data)
{
    m_stashed.emplace_back(data);
    return m_stashed.back();
}

IStringView IStringViewStash::stash(const QString &data)
{
    m_stashed.emplace_back(data.toUtf8());
    return m_stashed.back();
}

IStringView IStringViewStash::stash(std::string &&data)
{
    m_stashed.emplace_back(std::move(data));
    return m_stashed.back();
}

IStringView IStringViewStash::stash(const std::string &data)
{
    m_stashed.emplace_back(std::move(data));
    return m_stashed.back();
}

$PackageWebCoreEnd
