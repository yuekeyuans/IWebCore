#include "IStringData.h"

$PackageWebCoreBegin

IStringData::IStringData() : m_type(Type::Invalid) {}

IStringData::~IStringData() { clear(); }

IStringData::IStringData(const IStringData& other) : m_type(Type::Invalid) {
    copyFrom(other);
}

IStringData::IStringData(IStringData&& other) noexcept : m_type(Type::Invalid) {
    moveFrom(std::move(other));
}

IStringData& IStringData::operator=(const IStringData& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

IStringData& IStringData::operator=(IStringData&& other) noexcept {
    if (this != &other) {
        clear();
        moveFrom(std::move(other));
    }
    return *this;
}

IStringData::IStringData(const QByteArray& byteArray) : m_type(Type::QByteArray) {
    new (&m_qByteArray) QByteArray(byteArray);
}

IStringData::IStringData(QByteArray&& byteArray) noexcept : m_type(Type::QByteArray) {
    new (&m_qByteArray) QByteArray(std::move(byteArray));
}

IStringData::IStringData(const std::string& stdString) : m_type(Type::StdString) {
    new (&m_stdString) std::string(stdString);
}

IStringData::IStringData(std::string&& stdString) noexcept : m_type(Type::StdString) {
    new (&m_stdString) std::string(std::move(stdString));
}

IStringData::IStringData(IStringView stringView) : m_type(Type::IStringView) {
    new (&m_iStringView) IStringView(stringView);
}

IStringData& IStringData::operator=(const QByteArray& byteArray) {
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(byteArray);
    return *this;
}

IStringData& IStringData::operator=(QByteArray&& byteArray) noexcept {
    clear();
    m_type = Type::QByteArray;
    new (&m_qByteArray) QByteArray(std::move(byteArray));
    return *this;
}

IStringData& IStringData::operator=(const std::string& stdString) {
    clear();
    m_type = Type::StdString;
    new (&m_stdString) std::string(stdString);
    return *this;
}

IStringData& IStringData::operator=(std::string&& stdString) noexcept {
    clear();
    m_type = Type::StdString;
    new (&m_stdString) std::string(std::move(stdString));
    return *this;
}

IStringData& IStringData::operator=(IStringView stringView) {
    clear();
    m_type = Type::IStringView;
    new (&m_iStringView) IStringView(stringView);
    return *this;
}

IStringData& IStringData::operator=(std::nullptr_t) {
    clear();
    m_type = Type::Invalid;
    return *this;
}

IStringView IStringData::toStringView() const {
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

void IStringData::clear() {
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

void IStringData::copyFrom(const IStringData& other) {
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

void IStringData::moveFrom(IStringData&& other) noexcept {
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
