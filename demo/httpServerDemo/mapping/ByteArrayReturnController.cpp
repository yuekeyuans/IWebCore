#include "ByteArrayReturnController.h"

ByteArrayReturnController::ByteArrayReturnController()
{
    $ConstructController
}

QString ByteArrayReturnController::getArray1(IResponse &response)
{
    response.setStatus(IHttpStatus::NOT_FOND_404);
    response.setMime(IHttpMime::TEXT_HTML_UTF8);
    return "$bytes:hello world1";
}

IByteArrayResponse ByteArrayReturnController::getArray2()
{
    return "hello world2"_bytes;
}

QByteArray ByteArrayReturnController::getArray3()
{
    QByteArray a = QStringLiteral("hello world3").toUtf8();
    return a;
}

void ByteArrayReturnController::getArray4(IResponse &response)
{
    response.setStatus(IHttpStatus::OK_200);
    response.setMime(IHttpMime::TEXT_PLAIN);
    response.setContent("hello world4");
}


