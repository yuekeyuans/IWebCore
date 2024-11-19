#pragma once
#include <QtCore>
#include <IWebCore>

class UrlPatternController2 : public IHttpControllerInterface<UrlPatternController2, true>
{
    Q_GADGET
    $AsController(UrlPatternController2)

public:
    UrlPatternController2() = default;

    $GetMapping(url1, abc/<hello>)
    QString url1();

    $GetMapping(url2, abd/<number:int>)
    QString url2($Url(int, number));

//    $GetMapping(url3, abd/<number:int>/<number:double>)  // invalid
    $GetMapping(url3, abd/<number:int>/<number2:double>)
    QString url3($Url(int, number));
};






