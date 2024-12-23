#include "IString.h"

$PackageWebCoreBegin

IString::IString() : m_type(Type::IStringView) {}

IString::~IString()
{
    if(m_type == Type::QByteArray){
        delete static_cast<QByteArray*>(m_data);
    }else if(m_type == Type::StdString){
        delete static_cast<std::string*>(m_data);
    }
    m_data = nullptr;
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
    : m_type(Type::IStringView), m_stringView(istring->m_stringView)
{
}

// this just create view, no QByteArray
IString::IString(const QByteArray * data)
    : m_type(Type::IStringView), m_stringView(*data)
{
}

IString::IString(const std::string * stdStringPtr)
    : m_type(Type::IStringView), m_stringView(*stdStringPtr)
{
}

IString::IString(const char * data)
    : m_type(Type::StdString)
{
    m_data = new std::string(data);
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
}

IString::IString(const QByteArray& byteArray)
    : m_type(Type::QByteArray)
{
    m_data = new QByteArray(byteArray);
    m_stringView = IStringView(*static_cast<QByteArray*>(m_data));
}

IString::IString(QByteArray&& byteArray) noexcept : m_type(Type::QByteArray)
{
    m_data = new QByteArray(std::move(byteArray));
    m_stringView = IStringView(*static_cast<QByteArray*>(m_data));
}

IString::IString(const std::string& stdString) : m_type(Type::StdString)
{
    m_data = new std::string(stdString);
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
}

IString::IString(std::string&& stdString) noexcept : m_type(Type::StdString)
{
    m_data = new std::string(std::move(stdString));
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
}

IString::IString(IStringView stringView)
    : m_type(Type::IStringView), m_stringView(stringView)
{
}

IString &IString::operator=(const IString * value)
{
    clear();
    m_type = Type::IStringView;
    m_stringView = IStringView(*value);
    return *this;
}

IString &IString::operator=(const QByteArray *value)
{
    clear();
    m_type = Type::IStringView;
    m_stringView = IStringView(*value);
    return *this;
}

IString &IString::operator=(const std::string *value)
{
    clear();
    m_type = Type::IStringView;
    m_stringView = IStringView(*value);
    return *this;
}

IString &IString::operator=(const char *value)
{
    clear();
    m_type = Type::QByteArray;
    m_data = new std::string(value);
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString &IString::operator=(const QString & qstring)
{
    clear();
    m_type = Type::StdString;
    m_data = new std::string(qstring.toStdString());
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString& IString::operator=(const QByteArray& byteArray) {
    clear();
    m_type = Type::QByteArray;
    m_data = new QByteArray(byteArray);
    m_stringView = IStringView(*static_cast<QByteArray*>(m_data));
    return *this;
}

IString& IString::operator=(QByteArray&& byteArray) noexcept {
    clear();
    m_type = Type::QByteArray;
    m_data = new QByteArray(std::move(byteArray));
    m_stringView = IStringView(*static_cast<QByteArray*>(m_data));
    return *this;
}

IString& IString::operator=(const std::string& stdString) {
    clear();
    m_type = Type::StdString;
    m_data = new std::string(stdString);
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString& IString::operator=(std::string&& stdString) noexcept {
    clear();
    m_type = Type::StdString;
    m_data = new std::string(std::move(stdString));
    m_stringView = IStringView(*static_cast<std::string*>(m_data));
    return *this;
}

IString& IString::operator=(IStringView stringView) {
    clear();
    m_type = Type::IStringView;
    m_stringView = stringView;
    return *this;
}

IString& IString::operator=(std::nullptr_t) {
    clear();
    m_type = Type::IStringView;
    m_stringView = {};
    return *this;
}

bool IString::operator ==(const IString &that) const
{
    if(this == &that){
        return true;
    }
    return this->m_stringView.operator ==(that.m_stringView);
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
    return this->m_stringView < that.m_stringView;
}

std::size_t IString::length() const
{
    return m_stringView.length();
}

std::size_t IString::size() const
{
    return m_stringView.size();
}

bool IString::isSolid() const
{
    return m_type != Type::IStringView;
}

bool IString::isEmpty() const
{
    return m_stringView.empty();
}

IString& IString::solidify()
{
    if(m_type == Type::IStringView && !m_stringView.empty()){
        m_type = Type::StdString;
        m_data = new std::string(m_stringView.toStdString());
        m_stringView = IStringView(*static_cast<std::string*>(m_data));
    }

    return *this;
}

IStringViewList IString::split(char delimiter) const
{
    return m_stringView.split(delimiter);
}

IStringViewList IString::split(const IString &data) const
{
    return m_stringView.split(data.m_stringView);
}

bool IString::startWith(const IString & data) const
{
    return m_stringView.startWith(data.m_stringView);
}

bool IString::equalIgnoreCase(const IString & data) const
{
    return m_stringView.equalIgnoreCase(data.m_stringView);
}

bool IString::containIgnoreCase(const IString &data) const
{
    return m_stringView.containIgnoreCase(data.m_stringView);
}

QString IString::toQString() const
{
    return m_stringView.toQString();
}

std::string IString::toStdString() const
{
    return m_stringView.toStdString();
}

QByteArray IString::toQByteArray() const
{
    return m_stringView.toQByteArray();
}

IString::operator IStringView() const
{
    return m_stringView;
}

IString::operator bool() const
{
    return m_stringView.empty();
}

void IString::clear() {
    if(m_type == Type::QByteArray){
        delete static_cast<QByteArray*>(m_data);
    }else if(m_type == Type::StdString){
        delete static_cast<std::string*>(m_data);
    }
    m_data = nullptr;
    m_type = Type::IStringView;
}

void IString::copyFrom(const IString& other) {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            m_data = new QByteArray(*static_cast<QByteArray*>(other.m_data));
            m_stringView = IStringView(*static_cast<QByteArray*>(m_data));
            break;
        case Type::StdString:
            m_data = new std::string(*static_cast<std::string*>(other.m_data));
            m_stringView = IStringView(*static_cast<std::string*>(m_data));
            break;
        case Type::IStringView:
            m_stringView = other.m_stringView;
            break;
    }
}

void IString::moveFrom(IString&& other) noexcept {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            std::swap(this->m_data, other.m_data);
            m_stringView = IStringView(*static_cast<QByteArray*>(m_data));
            break;
        case Type::StdString:
            std::swap(this->m_data, other.m_data);
            m_stringView = IStringView(*static_cast<std::string*>(m_data));
            break;
        case Type::IStringView:
            m_stringView = other.m_stringView;
            break;
        default:
            break;
    }
    other.m_type = Type::IStringView;
}

$PackageWebCoreEnd
