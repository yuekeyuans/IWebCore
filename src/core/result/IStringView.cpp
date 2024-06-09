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

QByteArray IStringView::toQByteArray() const
{
    return QByteArray(data(), length());
}

IStringView IStringView::substr(const size_type _Off, size_type _Count) const
{
    return IStringView(std::string_view::substr(_Off, _Count));
}

IStringView IStringView::trimmed()
{
    auto left = find_first_not_of(' ');
    if (left == std::string_view::npos) {
        return "";
    }
    auto right = find_last_not_of(' ');
    return substr(left, right - left + 1);
}

QList<IStringView> IStringView::split(char delimiter) const
{
    QList<IStringView> tokens;
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

bool IStringView::startWith(IStringView prefix)
{
    return this->_Starts_with(prefix);
}

bool IStringView::endWith(IStringView suffix)
{
    return this->substr(this->size() - suffix.size()) == suffix;
}


$PackageWebCoreEnd
