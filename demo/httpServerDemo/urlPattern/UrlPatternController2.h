#pragma once
#include <QtCore>
#include <IWebCore>

class UrlPatternController2 : public IControllerInterface
{
    Q_GADGET
    $AsController(UrlPatternController2)

public:
    UrlPatternController2();

    $GetMapping(url1, abc/<hello>)
    QString url1();

    $GetMapping(url2, abd/<number:int>)
    QString url2($PathVar(int, number));

//    $GetMapping(url3, abd/<number:int>/<number:double>)  // invalid
    $GetMapping(url3, abd/<number:int>/<number2:double>)
    QString url3($PathVar(int, number));

};

//$RegisterController(UrlPatternController2)





