#include "IString.h"
#include "core/util/IMemoryObjectPool.h"

$PackageWebCoreBegin

namespace detail
{
    IMemoryObjectPool<std::string> s_pool;
}

IString::IString()
{
}

IString::~IString()
{
    clear();
}

IString::IString(const IString& other)
{
    copyFrom(other);
}

IString::IString(IString&& other) noexcept
{
    moveFrom(std::move(other));
}

IString& IString::operator=(const IString& other)
{
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

IString& IString::operator=(IString&& other) noexcept
{
    if (this != &other) {
        clear();
        moveFrom(std::move(other));
    }
    return *this;
}

IString::IString(const IString * istring)
    : m_type(Type::IStringView), m_view(istring->m_view)
{
}

IString::IString(const QByteArray * data)
    : m_type(Type::IStringView), m_view(*data)
{
}

IString::IString(const std::string * stdStringPtr)
    : m_type(Type::IStringView), m_view(*stdStringPtr)
{
}

IString::IString(const char * data)
    : m_type(Type::StdString)
{
    m_data = detail::s_pool.allocate(data);
    m_view = IStringView(*static_cast<std::string*>(m_data));
}

IString::IString(const QByteArray& byteArray)
    : m_type(Type::QByteArray)
{
    m_data = new QByteArray(byteArray);
    m_view = IStringView(*static_cast<QByteArray*>(m_data));
}

IString::IString(QByteArray&& byteArray) noexcept : m_type(Type::QByteArray)
{
    m_data = new QByteArray(std::move(byteArray));
    m_view = IStringView(*static_cast<QByteArray*>(m_data));
}

IString::IString(const std::string& stdString) : m_type(Type::StdString)
{
    m_data = detail::s_pool.allocate(stdString);
    m_view = IStringView(*static_cast<std::string*>(m_data));
}

IString::IString(std::string&& stdString) noexcept : m_type(Type::StdString)
{
    m_data = detail::s_pool.allocate(std::move(stdString));
    m_view = IStringView(*static_cast<std::string*>(m_data));
}

IString::IString(IStringView stringView)
    : m_type(Type::IStringView), m_view(stringView)
{
}

IString &IString::operator=(const IString * value)
{
    clear();
    m_type = Type::IStringView;
    m_view = IStringView(*value);
    return *this;
}

IString &IString::operator=(const QByteArray *value)
{
    clear();
    m_type = Type::IStringView;
    m_view = IStringView(*value);
    return *this;
}

IString &IString::operator=(const std::string *value)
{
    clear();
    m_type = Type::IStringView;
    m_view = IStringView(*value);
    return *this;
}

IString &IString::operator=(const char *value)
{
    clear();
    m_type = Type::QByteArray;
    m_data = detail::s_pool.allocate(value);
    m_view = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString &IString::operator=(const QString & qstring)
{
    clear();
    m_type = Type::StdString;
    m_data = detail::s_pool.allocate(qstring.toStdString());
    m_view = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString& IString::operator=(const QByteArray& byteArray) {
    clear();
    m_type = Type::QByteArray;
    m_data = new QByteArray(byteArray);
    m_view = IStringView(*static_cast<QByteArray*>(m_data));
    return *this;
}

IString& IString::operator=(QByteArray&& byteArray) noexcept {
    clear();
    m_type = Type::QByteArray;
    m_data = new QByteArray(std::move(byteArray));
    m_view = IStringView(*static_cast<QByteArray*>(m_data));
    return *this;
}

IString& IString::operator=(const std::string& stdString) {
    clear();
    m_type = Type::StdString;
    m_data = detail::s_pool.allocate(stdString);
    m_view = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString& IString::operator=(std::string&& stdString) noexcept {
    clear();
    m_type = Type::StdString;
    m_data = detail::s_pool.allocate(std::move(stdString));
    m_view = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString& IString::operator=(IStringView stringView) {
    clear();
    m_type = Type::IStringView;
    m_view = stringView;
    return *this;
}

IString& IString::operator=(std::nullptr_t) {
    clear();
    m_type = Type::IStringView;
    m_view = {};
    return *this;
}

bool IString::operator ==(const IString &that) const
{
    if(this == &that){
        return true;
    }
    return this->m_view.operator ==(that.m_view);
}

bool IString::operator !=(const IString & value) const
{
    return ! this->operator ==(value);
}

bool IString::operator <(const IString &that) const
{
    if(this == &that){
        return false;
    }
    return this->m_view < that.m_view;
}

std::size_t IString::length() const
{
    return m_view.length();
}

std::size_t IString::size() const
{
    return m_view.size();
}

bool IString::isSolid() const
{
    return m_type != Type::IStringView;
}

bool IString::isEmpty() const
{
    return m_view.empty();
}

IString& IString::solidify()
{
    if(m_type == Type::IStringView && !m_view.empty()){
        m_type = Type::StdString;
        m_data = detail::s_pool.allocate(m_view.toStdString());
        m_view = IStringView(*static_cast<std::string*>(m_data));
    }

    return *this;
}

IStringViewList IString::split(char delimiter) const
{
    return m_view.split(delimiter);
}

IStringViewList IString::split(const IString &data) const
{
    return m_view.split(data.m_view);
}

bool IString::startWith(const IString & data) const
{
    return m_view.startWith(data.m_view);
}

bool IString::equal(const IString &data) const
{
    return m_view == data.m_view;
}

bool IString::equalIgnoreCase(const IString & data) const
{
    return m_view.equalIgnoreCase(data.m_view);
}

bool IString::containIgnoreCase(const IString &data) const
{
    return m_view.containIgnoreCase(data.m_view);
}

QString IString::toQString() const
{
    return m_view.toQString();
}

std::string IString::toStdString() const
{
    if(m_type == Type::StdString){
        return *static_cast<std::string*>(m_data);
    }
    return m_view.toStdString();
}

QByteArray IString::toQByteArray() const
{
    if(m_type == Type::QByteArray){
        return *static_cast<QByteArray*>(m_data);
    }
    return m_view.toQByteArray();
}

IString::operator IStringView() const
{
    return m_view;
}

IString::operator bool() const
{
    return m_view.empty();
}

void IString::clear() {
    if(m_type == Type::QByteArray){
        delete static_cast<QByteArray*>(m_data);
    }else if(m_type == Type::StdString){
        detail::s_pool.deallocate(static_cast<std::string*>(m_data));
//        delete static_cast<std::string*>(m_data);
    }
    m_data = nullptr;
    m_type = Type::IStringView;
}

void IString::copyFrom(const IString& other) {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            m_data = new QByteArray(*static_cast<QByteArray*>(other.m_data));
            m_view = IStringView(*static_cast<QByteArray*>(m_data));
            break;
        case Type::StdString:
            m_data = detail::s_pool.allocate(*static_cast<std::string*>(other.m_data));
            m_view = IStringView(*static_cast<std::string*>(m_data));
            break;
        case Type::IStringView:
            m_view = other.m_view;
            break;
    }
}

void IString::moveFrom(IString&& other) noexcept {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            std::swap(this->m_data, other.m_data);
            m_view = IStringView(*static_cast<QByteArray*>(m_data));
            break;
        case Type::StdString:
            std::swap(this->m_data, other.m_data);
            m_view = IStringView(*static_cast<std::string*>(m_data));
            break;
        case Type::IStringView:
            m_view = other.m_view;
            break;
    }
}

$PackageWebCoreEnd
