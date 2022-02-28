#include "UrlPatternController2.h"

QString UrlPatternController2::url1()
{
    return "hello world";
}

QString UrlPatternController2::url3($Url(int, number))
{
    Q_UNUSED(number_url);
    return "hello world";
}

QString UrlPatternController2::url2($Url(int, number))
{
    Q_UNUSED(number_url);
    return "hello world";
}
