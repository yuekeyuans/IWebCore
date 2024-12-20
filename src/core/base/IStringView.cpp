#include "IStringView.h"

$PackageWebCoreBegin

IStringView::IStringView(const std::string &data)
    : std::string_view(data)
{
}

IStringView::IStringView(const QByteArray &data)
    : std::string_view(data.data(), data.length())
{
}

IStringView::IStringView(std::string_view data)
    : std::string_view(data.data(), data.length())
{
}

IStringView::IStringView(const char *data)
    : std::string_view(data)
{
}

IStringView::IStringView(const char *data, std::size_t length)
    : std::string_view(data, length)
{
}

IStringView::IStringView(const IStringView& view)
    : std::string_view(view.data(), view.length())
{
}

IWebCore::IStringView::operator QByteArray() const
{
    return toQByteArray();
}

bool IStringView::operator ==(const IStringView& data) const
{
    if(this->length() != data.length()){
        return false;
    }
    if(this->length() == 0 || this->data() == data.data()){    // empty equals empty
        return true;
    }
    return memcmp(this->data(), data.data(), this->length() * sizeof(IStringView::value_type)) == 0;
}

bool IStringView::operator !=(const IStringView &data) const
{
    return !this->operator ==(data);
}

bool IStringView::operator ==(const char * data) const
{
    return operator ==(IStringView(data));
}

bool IStringView::operator <(IStringView data) const
{
    return std::string_view(*this) < std::string_view(data);
}

uint IStringView::qHash(const IStringView *obj, uint seed)
{
    for (auto it=obj->cbegin(); it!=obj->cend(); it++) {
        seed ^= std::hash<char>{}(*it) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

QString IStringView::toQString() const
{
    return QString::fromLocal8Bit(data(), length());
}

std::string IStringView::toStdString() const
{
    return std::string(*this);
}

QByteArray IStringView::toQByteArray() const
{
    return QByteArray(data(), length());
}

asio::const_buffer IStringView::toAsioBuffer() const
{
    return asio::const_buffer(data(), length());
}

IStringView IStringView::substr(const size_type _Off, size_type _Count) const
{
    return IStringView(std::string_view::substr(_Off, _Count));
}

IStringView IStringView::trimmed()
{
    auto left = find_first_not_of(" \r\n\t");
    if (left == std::string_view::npos) {
        return "";
    }
    auto right = find_last_not_of(" \r\n\t");
    return substr(left, right - left + 1);
}

IStringViewList IStringView::split(char delimiter) const
{
    IStringViewList tokens;
    std::string_view::size_type start = 0;
    std::string_view::size_type end = this->find(delimiter);

    while (end != std::string_view::npos) {
        tokens.append(IStringView(this->substr(start, end - start)));
        start = end + 1;
        end = this->find(delimiter, start);
    }

    tokens.append(IStringView(this->substr(start, end)));
    return tokens;
}

IStringViewList IStringView::split(IStringView delimiter) const
{
    IStringViewList result;
    size_t start = 0;
    size_t end = find(delimiter);
    while (end != std::string_view::npos) {
        result.push_back(substr(start, end - start));
        start = end + delimiter.length();
        end = find(delimiter, start);
    }

    result.append(substr(start));
    return result;
}

bool IStringView::startWith(IStringView prefix) const
{
    return this->_Starts_with(prefix);
}

bool IStringView::endWith(IStringView suffix) const
{
//    if(this->size() < suffix.size()){
//        return false;
//    }
    return this->substr(this->size() - suffix.size()) == suffix;
}

bool IStringView::equalIgnoreCase(const std::string_view &data) const
{
    if (this->length() != data.length()) {
        return false;
    }
    if(this->operator ==(data)){
        return true;
    }

    const char* ptr1 = this->data();
    const char* ptr2 = data.data();
    for (size_t i = 0; i < length(); ++i) {
        if(ptr1[i] == ptr2[i]){
            continue;
        }
        if (std::tolower(ptr1[i]) != std::tolower(ptr2[i])) {
            return false;
        }
    }

    return true;
}

IStringViewList::IStringViewList(QList<IStringView> data)
    : QList<IStringView>(std::move(data))
{
}

$PackageWebCoreEnd
