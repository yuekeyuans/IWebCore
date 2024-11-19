#include "HttpReturnController.h"

HttpRturnController::HttpRturnController() : IHttpControllerInterface()
{
}

IHtmlResponse HttpRturnController::html1()
{
    return "<h1>hello world</h1>"_html;
}

IHtmlResponse HttpRturnController::html2()
{
    return QString("<h3>hello world</h3>");
}

IHtmlResponse HttpRturnController::html3()
{
    return "<h2>hello world</h2>";
}

QString HttpRturnController::html4()
{
    return "$html:<h1>hello world</h1>";
}

void HttpRturnController::html5(IResponse &response)
{
    response.setStatus(IHttpStatus::OK_200)
            .setMime(IHttpMime::TEXT_HTML_UTF8)
            .setContent("<h1>hello world</h1>");
}
