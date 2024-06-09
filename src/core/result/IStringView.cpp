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

QList<IStringView> IStringView::split(char delimiter)
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


//IStringView IStringView::trimmed()
//{
//    return {};
//}

$PackageWebCoreEnd
