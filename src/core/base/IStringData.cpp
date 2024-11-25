#include "IStringData.h"

$PackageWebCoreBegin

IStringData::IStringData()
{
}

IStringData::~IStringData()
{
    switch (m_type) {
    case Type::Invalid:
        return;
    case Type::IStringView:
        return;
    case Type::QByteArray:
        m_qByteArray.~QByteArray();
        return;
    case Type::StdString:
        m_stdString.~basic_string();
        break;
    }
}

IStringData::IStringData(const QString & value)
    : m_type(Type::QByteArray)
{
    new (&m_qByteArray)QByteArray(value.toUtf8());
}

IStringData::IStringData(QByteArray && value)
    : m_type(Type::QByteArray)
{
    new (&m_qByteArray)QByteArray(std::move(value));
}

IStringData::IStringData(const QByteArray &value)
    : m_type(Type::QByteArray)
{
    new (&m_qByteArray)QByteArray(value);
}

IStringData::IStringData(std::string && value)
    : m_type(Type::StdString)
{
    new (&m_stdString)std::string(std::move(value));
}

IStringData::IStringData(const std::string & value)
    : m_type(Type::StdString)
{
    new (&m_stdString)std::string(value);
}

IStringData::IStringData(IStringView view)
    : m_type(Type::IStringView)
{
    new (&m_iStringView)IStringView(view);
}

IStringView IStringData::toStringView() &
{
    switch (m_type) {
    case Type::Invalid:
        return {};
    case Type::IStringView:
        return m_iStringView;
    case Type::QByteArray:
        return IStringView(m_qByteArray);
    case Type::StdString:
        return IStringView(m_stdString);
    }
    return {};
}

$PackageWebCoreEnd
