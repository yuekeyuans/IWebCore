#include "TextReturnController.h"

TextReturnController::TextReturnController()
{
}

QString TextReturnController::text1()
{
    return "hello world";
}

QString TextReturnController::text_1()
{
    return "$text:hello world";
}

IPlainTextResponse TextReturnController::text2()
{
    return "hello world"_text;
}

IPlainTextResponse TextReturnController::text3()
{
    return QString("hello world");
}

IPlainTextResponse TextReturnController::text4()
{
    return "hello world";
}

void TextReturnController::text5(IResponse &response)
{
    response.setMime(IHttpMime::TEXT_PLAIN);
    response.setContent("hello world");
}
