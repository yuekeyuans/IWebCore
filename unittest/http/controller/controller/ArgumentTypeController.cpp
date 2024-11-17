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
