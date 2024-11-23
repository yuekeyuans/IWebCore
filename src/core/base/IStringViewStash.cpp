#include "IStringViewStash.h"

$PackageWebCoreBegin

IStringViewStash IGlobalStringViewStash::m_stash;

IStringView IStringViewStash::stash(const char *data)
{
    return stash(QByteArray(data));
}

IStringView IStringViewStash::stash(const QByteArray &data)
{
    m_stashed.emplace_back(data);
    return IStringView(m_stashed.back().data(), m_stashed.back().length());
}

IStringView IStringViewStash::stash(const QString &data)
{
    return stash(data.toUtf8());
}

IStringView IStringViewStash::stash(const std::string &data)
{
    return stash(QString::fromStdString(data));
}

IGlobalStringViewStash::IGlobalStringViewStash(const char *data)
{
    m_view = m_stash.stash(data);
}

IGlobalStringViewStash::IGlobalStringViewStash(const QByteArray &data)
{
    m_view = m_stash.stash(data);
}

IGlobalStringViewStash::IGlobalStringViewStash(const QString &data)
{
    m_view = m_stash.stash(data);
}

IGlobalStringViewStash::IGlobalStringViewStash(const std::string &data)
{
    m_view = m_stash.stash(data);
}

IGlobalStringViewStash::operator IStringView() const
{
    return m_view;
}

IStringView IGlobalStringViewStash::view() const
{
    return m_view;
}

$PackageWebCoreEnd
