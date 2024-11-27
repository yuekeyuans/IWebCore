#include "IString.h"

$PackageWebCoreBegin

IString::IString() : m_type(Type::Invalid) {}

IString::~IString() { clear(); }

IString::IString(const IString& other) : m_type(Type::Invalid)
{
    copyFrom(other);
}

IString::IString(IString&& other) noexcept : m_type(Type::Invalid)
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

IString::IString(const QByteArray * data) : m_type(Type::IStringView)
{
    new (&m_iStringView) IStringView(data->data(), data->length());
}

IString::IString(const QByteArray& byteArray) : m_type(Type::QByteArray)
{
    new (&m_qByteArray) QByteArray(byteArray);
}

IString::IString(QByteArray&& byteArray) noexcept : m_type(Type::QByteArray)
{
    new (&m_qByteArray) QByteArray(std::move(byteArray));
}

IString::IString(const std::string * stdStringPtr) : m_type(Type::IStringView)
{
    new (&m_iStringView) IStringView(stdStringPtr->data(), stdStringPtr->length());
}

IString::IString(const std::string& stdString) : m_type(Type::StdString)
{
    new (&m_stdString) std::string(stdString);
}

IString::IString(std::string&& stdString) noexcept : m_type(Type::StdString)
{
    new (&m_stdString) std::string(std::move(stdString));
}

IString::IString(IStringView stringView) : m_type(Type::IStringView)
{
    new (&m_iStringView) IStringView(stringView);
}

IString &IString::operator=(const QString & qstring)
{
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(qstring.toUtf8());
    return *this;
}

IString& IString::operator=(const QByteArray& byteArray) {
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(byteArray);
    return *this;
}

IString& IString::operator=(QByteArray&& byteArray) noexcept {
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(std::move(byteArray));
    return *this;
}

IString& IString::operator=(const std::string& stdString) {
    clear();
    m_type = Type::StdString;
    new (&m_stdString) std::string(stdString);
    return *this;
}

IString& IString::operator=(std::string&& stdString) noexcept {
    clear();
    m_type = Type::StdString;
    new (&m_stdString) std::string(std::move(stdString));
    return *this;
}

IString& IString::operator=(IStringView stringView) {
    clear();
    m_type = Type::IStringView;
    new (&m_iStringView) IStringView(stringView);
    return *this;
}

IString& IString::operator=(std::nullptr_t) {
    clear();
    m_type = Type::Invalid;
    return *this;
}

// TODO: 这些是都要优化的,但是可以等一等.
bool IString::operator ==(const IString &that) const
{
    if(this == &that){
        return true;
    }
    return this->toStringView() == that.toStringView();
}

bool IString::operator <(const IString &that) const
{
    if(this == &that){
        return false;
    }
    return this->toStringView() < that.toStringView();
}

bool IString::isEmpty() const
{
    switch (m_type) {
    case Type::QByteArray:
        return m_qByteArray.isEmpty();
    case Type::StdString:
        return m_stdString.empty();
    case Type::IStringView:
        return m_iStringView.empty();
    default:
        return true;
    }
}

IStringView IString::toStringView() const {
    switch (m_type) {
        case Type::QByteArray:
            return IStringView(m_qByteArray.constData(), m_qByteArray.size());
        case Type::StdString:
            return IStringView(m_stdString.data(), m_stdString.size());
        case Type::IStringView:
            return m_iStringView;
        default:
            return {};
    }
}

void IString::clear() {
    switch (m_type) {
        case Type::QByteArray:
            m_qByteArray.~QByteArray();
            break;
        case Type::StdString:
            m_stdString.~basic_string();
            break;
        case Type::IStringView:
            m_iStringView.~IStringView();
            break;
        default:
            break;
    }
    m_type = Type::Invalid;
}

void IString::copyFrom(const IString& other) {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            new (&m_qByteArray) QByteArray(other.m_qByteArray);
            break;
        case Type::StdString:
            new (&m_stdString) std::string(other.m_stdString);
            break;
        case Type::IStringView:
            new (&m_iStringView) IStringView(other.m_iStringView);
            break;
        default:
            break;
    }
}

void IString::moveFrom(IString&& other) noexcept {
    m_type = other.m_type;
    switch (other.m_type) {
        case Type::QByteArray:
            new (&m_qByteArray) QByteArray(std::move(other.m_qByteArray));
            break;
        case Type::StdString:
            new (&m_stdString) std::string(std::move(other.m_stdString));
            break;
        case Type::IStringView:
            new (&m_iStringView) IStringView(other.m_iStringView);
            break;
        default:
            break;
    }
    other.m_type = Type::Invalid;
}

$PackageWebCoreEnd
