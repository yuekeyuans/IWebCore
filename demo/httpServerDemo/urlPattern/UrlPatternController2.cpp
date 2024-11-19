#include "UrlPatternController2.h"

UrlPatternController2::UrlPatternController2()
{
    $ConstructController
}

QString UrlPatternController2::url1()
{
    return "hello world";
}

QString UrlPatternController2::url3($PathVar (int, number))
{
    Q_UNUSED(number_path);
    return "hello world";
}

QString UrlPatternController2::url2($PathVar(int, number))
{
    Q_UNUSED(number_path);
    return "hello world";
}
