#include "ReqRespOperatorOverrideController.h"

void ReqRespOperatorOverrideController::testResp_getHeader(IResponse &response)
{
    response.setMime(IHttpMime::TEXT_PLAIN);
    response.setStatus(IHttpStatus::OK_200);
    assert(response["yuekeyuan"].isEmpty());
    response["yuekeyuan"] = "ginus";
    response << "ginus";
}

QString ReqRespOperatorOverrideController::testReq_getHeader(IRequest &request)
{
    qDebug() << request["yuekeyuan"];
    return request["yuekeyuan"];
}

void ReqRespOperatorOverrideController::test_respInputOverrid(IResponse &response)
{
    IPlainTextResponse textResponse("hello world");
    response << &textResponse;
}

void ReqRespOperatorOverrideController::test_respInputRefOverride(IResponse &response)
{
    IPlainTextResponse textResponse("hello world");
    response << textResponse;
}
