#include "IString.h"

$PackageWebCoreBegin

IString::IString() : m_type(Type::IStringView) {}

IString::~IString()
{
    if(m_type == Type::QByteArray){
        m_qByteArray.~QByteArray();
    }else if(m_type == Type::StdString){
        m_stdString.~basic_string();
    }
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
    new (&m_stdString) std::string(data);
    m_stringView = IStringView(m_stdString);
}


IString::IString(const QByteArray& byteArray)
    : m_type(Type::QByteArray)
{
    new (&m_qByteArray) QByteArray(byteArray);
    m_stringView = IStringView(m_qByteArray);
}

// this can be optimised
IString::IString(QByteArray&& byteArray) noexcept : m_type(Type::QByteArray)
{
    new (&m_qByteArray) QByteArray(std::move(byteArray));
    m_stringView = IStringView(m_qByteArray);
}

IString::IString(const std::string& stdString) : m_type(Type::StdString)
{
    new (&m_stdString) std::string(stdString);
    m_stringView = IStringView(m_stdString);
}

IString::IString(std::string&& stdString) noexcept : m_type(Type::StdString)
{
    new (&m_stdString) std::string(std::move(stdString));
    m_stringView = IStringView(m_stdString);
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
    new(&m_qByteArray) QByteArray(value);
    m_stringView = IStringView(m_qByteArray);
    return *this;
}

IString &IString::operator=(const QString & qstring)
{
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(qstring.toUtf8());
    m_stringView = IStringView(m_qByteArray);
    return *this;
}

IString& IString::operator=(const QByteArray& byteArray) {
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(byteArray);
    m_stringView = IStringView(m_qByteArray);
    return *this;
}

IString& IString::operator=(QByteArray&& byteArray) noexcept {
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(std::move(byteArray));
    m_stringView = IStringView(m_qByteArray);
    return *this;
}

IString& IString::operator=(const std::string& stdString) {
    clear();
    m_type = Type::StdString;
    new (&m_stdString) std::string(stdString);
    m_stringView = IStringView(m_stdString);
    return *this;
}

IString& IString::operator=(std::string&& stdString) noexcept {
    clear();
    m_type = Type::StdString;
    new (&m_stdString) std::string(std::move(stdString));
    m_stringView = IStringView(m_stdString);
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

// TODO: 这些是都要优化的,但是可以等一等.
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
        new (&m_stdString) std::string(m_stringView.toStdString());
        m_stringView = IStringView(m_stdString);
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

IString::operator IStringView() const
{
    return m_stringView;
}

IString::operator bool() const
{
    return m_stringView.empty();
}

void IString::clear() {
    switch (m_type) {
        case Type::QByteArray:
            m_qByteArray.~QByteArray();
            break;
        case Type::StdString:
            m_stdString.~basic_string();
            break;
    }
}

void IString::copyFrom(const IString& other) {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            new (&m_qByteArray) QByteArray(other.m_qByteArray);
            m_stringView = IStringView(m_qByteArray);
            break;
        case Type::StdString:
            new (&m_stdString) std::string(other.m_stdString);
            m_stringView = IStringView(m_stdString);
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
            new (&m_qByteArray) QByteArray(std::move(other.m_qByteArray));
            m_stringView = IStringView(m_qByteArray);
            break;
        case Type::StdString:
            new (&m_stdString) std::string(std::move(other.m_stdString));
            m_stringView = IStringView(m_stdString);
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
