#pragma once

#include <IWeb/IControllerInterface>

class UrlPatternController : public IHttpControllerInterface<UrlPatternController, false>
{
    Q_GADGET
    $AsController(UrlPatternController)

public:
    UrlPatternController();

    $GetMapping(url1, <>)
    QString url1(IRequest &request);

    $GetMapping(url2, <hello>)
    QString url2();

    $GetMapping(url3, <:int>)
    QString url3();

    $GetMapping(url4, <name1:uuid>)
    QString url4();

    $GetMapping(url5, <name:>)
    QString url5();

    $GetMapping(url6, <:>)
    QString url6();

    $GetMapping(url7, <reg:abc:dsad>)
    QString url7();

    $GetMapping(url8, <:abc:asd>)
    QString url8();

    $GetMapping(url9, <::asd>)
    QString url9();

    $GetMapping(url10, <::>)
    QString url10();
};

