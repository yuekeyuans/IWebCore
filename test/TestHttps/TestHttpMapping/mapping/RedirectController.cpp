#include "RedirectController.h"

RedirectController::RedirectController()
{
}

IRedirectResponse RedirectController::redirect1()
{
    return IRedirectResponse("http://www.baidu.com");
}

QString RedirectController::redirect2()
{
    return "$redirect:http://www.baidu.com";
}

IRedirectResponse RedirectController::redirect3()
{
    IRedirectResponse response("http://www.baidu.com/s");
//    response.addAttribute("word", QStringLiteral("约为"));
    return response;
}

IRedirectResponse RedirectController::redirect4()
{
    return "http://www.baidu.com"_redirect;
}

IJsonResponse RedirectController::redirect5()
{
    return "http://www.baidu.com"_redirect;
}
