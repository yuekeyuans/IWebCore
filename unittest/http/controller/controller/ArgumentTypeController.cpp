#include "ArgumentTypeController.h"


QString ArgumentTypeController::emptyRequest()
{
    return "hello world";
}

QString ArgumentTypeController::irequestRef(IRequest &request)
{
    return request.url();
}

QString ArgumentTypeController::constIRequestRef(const IRequest & req)
{
    return req.url();
}

QString ArgumentTypeController::irequest(IRequest)
{
    return "hello world";
}

QString ArgumentTypeController::iresponseRef(IResponse &response)
{
    response.setHeader("hello", "world");
    return "hello world";
}
