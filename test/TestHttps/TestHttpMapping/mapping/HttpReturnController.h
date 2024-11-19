#pragma once

#include <IWeb/IControllerInterface>

class HttpRturnController : public IHttpControllerInterface<HttpRturnController>
{
    Q_GADGET
    $AsController(HttpRturnController)
public:
    HttpRturnController();

    $GetMapping(html1, html1)
    IHtmlResponse html1();

    $GetMapping(html2, html2)
    IHtmlResponse html2();

    $GetMapping(html3, html3)
    IHtmlResponse html3();

    $GetMapping(html4, html4)
    QString html4();

    $GetMapping(html5, html5)
    void html5(IResponse &response);
};
