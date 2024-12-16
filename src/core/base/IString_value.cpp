#include "IString.h"
#include <charconv>
#include <string_view>

$PackageWebCoreBegin

namespace detail
{
    template <typename T>
    T string_view_to(const IStringView& str, bool& ok) {
        T result{};
        if (str.empty()) {
            ok = false;
            return result;
        }

        auto val = std::from_chars(&*str.begin(), &*str.end(), result);
        if (val.ec != std::errc()) {
            ok = false;
            return result;
        }
        ok = true;
        return result;
    }
}

#define STRING_VIEW_CREATE(Class)                                   \
template<>                                                          \
Class IString::value< Class >(bool& ok)   const {                   \
    return detail::string_view_to< Class >(m_stringView, ok);       \
}
STRING_VIEW_CREATE(ushort)
STRING_VIEW_CREATE(short)
STRING_VIEW_CREATE(uint)
STRING_VIEW_CREATE(int)
STRING_VIEW_CREATE(unsigned long)
STRING_VIEW_CREATE(long)
STRING_VIEW_CREATE(unsigned long long)
STRING_VIEW_CREATE(long long)
STRING_VIEW_CREATE(float)
STRING_VIEW_CREATE(double)
#undef STRING_VIEW_CREATE

template<>
bool IString::value<bool>(bool& ok) const
{
    if(m_stringView == "true"){
        ok = true;
        return true;
    }
    if(m_stringView == "false"){
        ok = true;
        return false;
    }
    ok = false;
    return !m_stringView.empty();
}

template<>
unsigned char IString::value<unsigned char>(bool& ok) const
{
    auto value = detail::string_view_to<unsigned short>(m_stringView, ok);
    if(ok && value > std::numeric_limits<unsigned char>::max()){
        ok = false;
    }
    return static_cast<unsigned char>(value);
}

template<>
signed char IString::value<signed char>(bool& ok) const
{
    auto value = detail::string_view_to<short>(m_stringView, ok);
    if(ok && (value > std::numeric_limits<signed char>::max() || value < std::numeric_limits<signed char>::min())){
        ok = false;
    }
    return static_cast<signed char>(value);
}

template<>
QString IString::value<QString>(bool& ok) const
{
    ok = true;
    return toQString();
}

template<>
QByteArray IString::value<QByteArray>(bool& ok) const
{
    ok = true;
    return toQByteArray();
}

template<>
std::string IString::value<std::string>(bool& ok) const
{
    ok = true;
    return toStdString();
}

template<>
IString IString::value<IString>(bool& ok) const
{
    ok = true;
    return *this;
}


#define VIEW_PTR_CREATE(Class)                                       \
template<>                                                           \
Class * IString::valuePtr< Class >(bool& ok) const {                 \
    auto ptr = new Class (value< Class >(ok));                       \
    return ptr;                                                      \
}
VIEW_PTR_CREATE(bool)
VIEW_PTR_CREATE(unsigned char)
VIEW_PTR_CREATE(signed char)
VIEW_PTR_CREATE(unsigned short)
VIEW_PTR_CREATE(short)
VIEW_PTR_CREATE(unsigned int)
VIEW_PTR_CREATE(int)
VIEW_PTR_CREATE(unsigned long)
VIEW_PTR_CREATE(long)
VIEW_PTR_CREATE(unsigned long long)
VIEW_PTR_CREATE(long long)
VIEW_PTR_CREATE(float)
VIEW_PTR_CREATE(double)
VIEW_PTR_CREATE(QString)
VIEW_PTR_CREATE(QByteArray)
VIEW_PTR_CREATE(std::string)
VIEW_PTR_CREATE(IString)
#undef VIEW_PTR_CREATE

$PackageWebCoreEnd
